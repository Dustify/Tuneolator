#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"

class Control {
public:
volatile static int16 activeNotes[polyphony];

static void init() {
	for (uint8 i = 0; i < polyphony; i++) {
		activeNotes[i] = -1;
	}
}

static void pause(double duration) {
	delay(250 * duration);
}

static void stopNote(uint8 note) {
	for (uint8 i = 0; i < polyphony; i++) {
		if (activeNotes[i] == note) {
			activeNotes[i] = -1;
			return;
		}
	}
}

static void playNote(uint8 note, double duration) {
	uint8 nextAvailable = -1;

	for (uint8 i = 0; i < polyphony; i++) {
		if (activeNotes[i] == note) {
			return;
		}

		if (activeNotes[i] == -1) {
			nextAvailable = i;
			break;
		}
	}

	if (nextAvailable == -1) {
		return;
	}

	activeNotes[nextAvailable] = note;

	if (duration > 0) {
		pause(duration);
		stopNote(note);
	}
}
};

volatile int16 Control::activeNotes[polyphony] = {};

#endif
