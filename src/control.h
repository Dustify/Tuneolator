#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"
#include "lfo.h"
#include "wavetable.h"
#include "activeNote.h"

class Control {
public:
static ActiveNote activeNotes[polyphony];

static void stopNote(uint8 note) {
	for (uint8 i = 0; i < polyphony; i++) {
		if (activeNotes[i].active && activeNotes[i].note == note) {
			activeNotes[i].stop();
		}
	}
}

static void playNote(uint8 note) {
	for (uint8 i = 0; i < polyphony; i++) {
		if (!activeNotes[i].active) {
			activeNotes[i].start(note);
			return;
		}
	}
}

static void init() {
	// TODO: configurable
	GPIOA->regs->CRL = 0x33333333;

	for (uint8 i = 0; i < polyphony; i++) {
		activeNotes[i].init();
	}

	Lfo::init();
	Notes::init();
	Wavetable::init();
}

static void tick() {
	int16 result = 0;

	uint8 activeNoteCount = 0;

	for (uint8 i = 0; i < polyphony; i++) {
		if (activeNotes[i].active) {
			result += activeNotes[i].tick();
			activeNoteCount++;
		}
	}

	result += Lfo::tick();

	// TODO: implement this more better
	result = result / activeNoteCount;

	result += Wavetable::halfAmplitudes;

	result = result > 255 ? 255 : result;
	result = result < 0 ? 0 : result;

	GPIOA->regs->ODR = result;
}
};

ActiveNote Control::activeNotes[polyphony];

#endif
