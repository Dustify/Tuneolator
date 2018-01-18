#ifndef LFO_H
#define LFO_H

#include <Arduino.h>
#include "note.h"
#include "config.h"
#include "wavetable.h"
#include "fixed.h"
#include "config.h"

class Lfo {
public:
static int8_t* wavetable;
static uint32_t tickCount;
static uint32_t ticks;
static uint8_t factor;

static bool active() {
	return
	    wavetable != NULL &&
	    ticks > 0 &&
	    factor > 0;
}

static void setWavetable(uint8_t value) {
	if (value < 42) {
		wavetable = NULL;
		return;
	}

	if (value < 84) {
		wavetable = Wavetable::low;
		return;
	}

	wavetable = Wavetable::high;
}

static void setFrequency(uint8_t value) {
	if (value == 0) {
		ticks = 0;
		return;
	}

	double frequency = (value / 127.0) * maxLfoFrequency;
	ticks = round(ticks_per_second / frequency);
}

static void setFactor(uint8_t value) {
	factor = value;    // / 127.0;
}

static int8_t tick() {
	if (wavetable == NULL) {
		return 0;
	}

	if (tickCount >= ticks) {
		tickCount = 0;
	}

	uint16_t phase = Fixed::factorLfo(phases, tickCount, ticks);
	int8_t result = Fixed::factorLfoVolume(wavetable[phase], factor, midiMaxValue);

	tickCount++;

	return result;
}
};

int8_t* Lfo::wavetable;
uint32_t Lfo::tickCount;
uint32_t Lfo::ticks;
uint8_t Lfo::factor;

#endif
