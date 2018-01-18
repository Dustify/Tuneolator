#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"
#include "lfo.h"
#include "wavetable.h"
#include "activeNote.h"

class Control {
public:
static uint8_t volume;
static ActiveNote activeNotes[polyphony];

static void stopNote(uint8_t note) {
	for (uint8_t i = 0; i < polyphony; i++) {
		if (activeNotes[i].active && activeNotes[i].note == note) {
			activeNotes[i].stop();
		}
	}
}

static void playNote(uint8_t note, uint8_t velocity) {
	if (velocity == 0) {
		stopNote(note);
		return;
	}

	uint8_t actualPolyphony = polyphony;

	// remove one note if LFO is active
	if (Lfo::active()) {
		actualPolyphony--;
	}

	for (uint8_t i = 0; i < actualPolyphony; i++) {
		// re-use note if already set
		if (activeNotes[i].note == note) {
			activeNotes[i].start(note, velocity);
			return;
		}
	}

	for (uint8_t i = 0; i < actualPolyphony; i++) {
		// find an inactive note
		if (!activeNotes[i].active) {
			activeNotes[i].start(note, velocity);
			return;
		}
	}

	for (uint8_t i = 0; i < actualPolyphony; i++) {
		// if we've got this far, all notes are active
		// find one in release (available)
		if (activeNotes[i].available) {
			activeNotes[i].start(note, velocity);
			return;
		}
	}
}

static void init() {
	// TODO: configurable
	GPIOA->regs->CRL = 0x33333333;

	for (uint8_t i = 0; i < polyphony; i++) {
		activeNotes[i].init();
	}

	Notes::init();
	Wavetable::init();
}

static void setVolume(uint8_t value) {
	volume = value;
}

static void tick() {
	int16_t result = 0;

	for (uint8_t i = 0; i < polyphony; i++) {
		result += activeNotes[i].tick();
	}

	// apply lfo
	result += Lfo::tick();

	// volume
	result = Fixed::factorVolume(result, volume, midiMaxValue);

	// shift output to positive
	result += Wavetable::halfAmplitudes;

	// hard clipping, add indicator?
	result = result > 255 ? 255 : result;
	result = result < 0 ? 0 : result;

	GPIOA->regs->ODR = result;
}
};

ActiveNote Control::activeNotes[polyphony];
uint8_t Control::volume = 64;

#endif
