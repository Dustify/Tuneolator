#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"
#include "lfo.h"
#include "wavetable.h"
#include "activeNote.h"

class Control {
public:
static uint8 volume;
static ActiveNote activeNotes[polyphony];

static void stopNote(uint8 note) {
	for (uint8 i = 0; i < polyphony; i++) {
		if (activeNotes[i].active && activeNotes[i].note == note) {
			activeNotes[i].stop();
		}
	}
}

static void playNote(uint8 note, uint8 velocity) {
	if (velocity == 0) {
		stopNote(note);
		return;
	}

	int8 nextAvailable = -1;

	for (uint8 i = 0; i < polyphony; i++) {
		// re-use existing note if it matches
		if (activeNotes[i].active && activeNotes[i].note == note) {
			nextAvailable = i;
			break;
		}

		// just find next inactive note
		if (!activeNotes[i].active) {
			nextAvailable = i;
		}
	}

	// if there's nothing available, do nothing
	if (nextAvailable == -1) {
		return;
	}

	activeNotes[nextAvailable].start(note, velocity);
}

static void init() {
	// TODO: configurable
	GPIOA->regs->CRL = 0x33333333;

	for (uint8 i = 0; i < polyphony; i++) {
		activeNotes[i].init();
	}

	Notes::init();
	Wavetable::init();
}

static void setVolume(uint8 value) {
	volume = value;
}

static void tick() {
	int16 result = 0;

	for (uint8 i = 0; i < polyphony; i++) {
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
uint8 Control::volume = 64;

#endif
