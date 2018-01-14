#ifndef CONTROLVALUES_H
#define CONTROLVALUES_H
#include <arduino.h>
#include "wavetable.h"
#include "lfo.h"
#include "activenote.h"

class ControlValues {
public:

static void set(uint8 id, uint8 value) {
	if (id == controlRelease) {
		ActiveNote::setRelease(value);
		return;
	}

	// set lfo wavetable
	if (id == controlLfoWavetable) {
		Lfo::setWavetable(value);
		return;
	}

	// set lfo frequency
	if (id == controlLfoFrequency) {
		Lfo::setFrequency(value);
		return;
	}

	// set lfo factor
	if (id == controlLfoFactor) {
		Lfo::setFactor(value);
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

#endif
