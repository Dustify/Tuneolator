#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include "control.h"
#include "controlValues.h"

class Midi {
public:
static void init() {
	Control::init();

	// remap serial 1 from A9/10 to B6/7
	afio_remap(AFIO_REMAP_USART1);
	gpio_set_mode(GPIOB, 6, GPIO_AF_OUTPUT_PP);
	gpio_set_mode(GPIOB, 7, GPIO_INPUT_FLOATING);

	Serial.begin(31250);
}

static uint8 message[3];
static uint8 position;

static void processMessage() {
	uint8 type = (message[0] & 0b01110000) >> 4;
	uint8 channel = message[0] & 0b00001111;
	uint8 note = message[1] & 0b01111111;
	uint8 velocity = message[2] & 0b01111111;

	if (channel == midiChannel) {
		// note off
		if (type == 0) {
			Control::stopNote(note);
		}

		// note on
		if (type == 1) {
			Control::playNote(note, velocity);
		}

		// control change
		if (type == 3) {
			ControlValues::set(note, velocity);
		}

		// reset position to second byte in case we get any 'follow-on' messages
		position = 1;
	}
}

static void read() {
	uint8 value = Serial.read();

	Serial.println(value);

	// first byte
	if (value > 127) {
		message[0] = value;
		position = 1;

		return;
	}

	// second and third bytes
	if (position < 3) {
		message[position] = value;
		position++;

		// all bytes received, time to process
		if (position == 3) {
			processMessage();
		}
	}

	if (position == 3) {

	}
}

static void process() {
	while (Serial.available()) {
		read();
	}
}
};

uint8 Midi::message[3];
uint8 Midi::position;

#endif
