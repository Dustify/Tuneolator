#ifndef LFO_H
#define LFO_H

#include <Arduino.h>
#include "note.h"
#include "config.h"
#include "wavetable.h"
#include "fixed.h"

class Lfo {
public:
static int8* wavetable;
static uint16 tickCount;
static uint16 ticks;
static uint8 factor;

static void setWavetable(uint8 value) {
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

static void setFrequency(uint8 value) {
	double frequency = (value / 127.0) * maxLfoFrequency;
	ticks = round(ticks_per_second / frequency);
}

static void setFactor(uint8 value) {
	factor = value;// / 127.0;
}

static int8 tick() {
	if (wavetable == NULL) {
		return 0;
	}

	if (tickCount >= ticks) {
		tickCount = 0;
	}

	uint16 phase = Fixed::factor(phases, tickCount, ticks);
	int8 result = Fixed::factor(wavetable[phase], factor, 127);

	tickCount++;

	return result;
}
};

int8* Lfo::wavetable;
uint16 Lfo::tickCount;
uint16 Lfo::ticks;
uint8 Lfo::factor;

#endif
