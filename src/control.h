#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"
#include "notes.h"
#include "lfo.h"
#include "wavetable.h"

class Control {
public:
volatile static int8 activeNote;
volatile static int8* wavetable;

static void pause(double duration) {
	delay(250 * duration);
}

static void stopNote() {
	activeNote = -1;
}

static void playNote(uint8 note, double duration) {
	activeNote = note;

	if (duration > 0) {
		pause(duration);
		stopNote();
	}
}

static void init() {
	GPIOA->regs->CRL = 0x33333333;

	Lfo::init();
	Notes::init();
	Wavetable::init();
}

static void setWavetable(int8* value) {
	wavetable = value;
}

static void tick() {
	int16 result = 0;

	if (Control::activeNote != -1) {
		int16 phase = Notes::notes[Control::activeNote].tick();
		result += wavetable[phase];
	}

	result += Lfo::tick();

	result += Wavetable::halfAmplitudes;

	result = result > 255 ? 255 : result;
	result = result < 0 ? 0 : result;

	GPIOA->regs->ODR = result;
}
};

volatile int8 Control::activeNote = -1;
volatile int8* Control::wavetable = NULL;

#endif
