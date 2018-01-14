#ifndef CONTROLVALUES_H
#define CONTROLVALUES_H
#include <arduino.h>
#include "wavetable.h"
#include "lfo.h"

class ControlValues {
public:
static uint8 values[128];

static void set(uint8 id, uint8 value) {
	// generic assignment here
	values[id] = value;

	// set lfo wavetable
	if (id == controlLfoWavetable) {
		if (value < 32) {
			Lfo::wavetable = NULL;
			return;
		}

		if (value < 64) {
			Lfo::wavetable = Wavetable::sine;
			return;
		}

		if (value < 96) {
			Lfo::wavetable = Wavetable::sawtooth;
			return;
		}

		Lfo::wavetable = Wavetable::triangle;
		return;
	}

	// set lfo frequency
	if (id == controlLfoFrequency) {
		Lfo::frequency = (value / 127.0) * 20.0;
		Lfo::init();
		return;
	}

	// set lfo factor
	if (id == controlLfoFactor) {
		Lfo::factor = value / 127.0;
		Lfo::init();
		return;
	}

	// set low wavetable
	if (id == controlLowWavetable) {
		if (value < 43) {
			Wavetable::currentLow = Wavetable::sine;
			return;
		}

		if (value < 86) {
			Wavetable::currentLow = Wavetable::sawtooth;
			return;
		}

		Wavetable::currentLow = Wavetable::triangle;
		return;
	}

	// set split
	if (id == controlSplit) {
		Wavetable::split = value;
		return;
	}

	// set high wavetable
	if (id == controlHighWavetable) {
		if (value < 43) {
			Wavetable::currentHigh = Wavetable::sine;
			return;
		}

		if (value < 86) {
			Wavetable::currentHigh = Wavetable::sawtooth;
			return;
		}

		Wavetable::currentHigh = Wavetable::triangle;
		return;
	}
}
};

uint8 ControlValues::values[128];

#endif
