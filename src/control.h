#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"
#include "notes.h"
#include "lfo.h"
#include "wavetable.h"

class Control {
public:
volatile static int8 activeNotes[polyphony];
volatile static int8* wavetable;

static void stopNote(uint8 note) {
	for (uint8 i = 0; i < polyphony; i++) {
		if (activeNotes[i] == note) {
			activeNotes[i] = -1;
		}
	}
}

static void playNote(uint8 note) {
	for (uint8 i = 0; i < polyphony; i++) {
		if (activeNotes[i] == -1) {
			activeNotes[i] = note;
			return;
		}
	}
}

static void init() {
	// TODO: configurable
	GPIOA->regs->CRL = 0x33333333;

	for (uint8 i = 0; i < polyphony; i++) {
		activeNotes[i] = -1;
	}

	Lfo::init();
	Notes::init();
	Wavetable::init();
}

static void setWavetable(int8* value) {
	wavetable = value;
}

static void tick() {
	int16 result = 0;

	uint8 activeNoteCount = 0;

	for (uint8 i = 0; i < polyphony; i++) {
		int8 activeNote = activeNotes[i];

		if (activeNote != -1) {
			int16 phase = Notes::notes[activeNote].tick();
			result += wavetable[phase];
			activeNoteCount++;
		}
	}

	result += Lfo::tick();

	result = result / activeNoteCount;

	result += Wavetable::halfAmplitudes;


	result = result > 255 ? 255 : result;
	result = result < 0 ? 0 : result;

	GPIOA->regs->ODR = result;
}
};

volatile int8 Control::activeNotes[polyphony];
volatile int8* Control::wavetable = NULL;

#endif
