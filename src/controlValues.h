#ifndef CONTROLVALUES_H
#define CONTROLVALUES_H
#include <arduino.h>
#include "wavetable.h"
#include "lfo.h"
#include "activenote.h"
#include "control.h"

class ControlValues {
public:

static void set(uint8_t id, uint8_t value) {
	// set attack
	if (id == controlAttack) {
		ActiveNote::setAttack(value);
		return;
	}

	#ifdef ENABLE_DECAY_SUSTAIN
	// set decay
	if (id == controlDecay) {
		ActiveNote::setDecay(value);
		return;
	}

	// set sustain
	if (id == controlSustain) {
		ActiveNote::setSustain(value);
		return;
	}
	#endif

	// set release
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
		Wavetable::setLow(value);
		return;
	}

	// set split
	if (id == controlSplit) {
		Wavetable::setSplit(value);
		return;
	}

	// set high wavetable
	if (id == controlHighWavetable) {
		Wavetable::setHigh(value);
		return;
	}

	// set volume
	if (id == controlVolume) {
		Control::setVolume(value);
		return;
	}
}
};

#endif
