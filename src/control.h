#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"

class Control {
public:
volatile static int8 activeNote;

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
};

volatile int8 Control::activeNote = -1;

#endif
