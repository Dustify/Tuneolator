#ifndef LFO_H
#define LFO_H

#include <Arduino.h>
#include "note.h"
#include "config.h"

class Lfo {
public:
static int8* wavetable;
static uint16 tickCount;
static uint16 ticks;
static float phasesPerTick;
static float frequency;
static float factor;

static void init() {
	if (frequency == 0) {
		frequency = 0.1;
	}

	float fTicks = ticks_per_second / frequency;
	ticks = round(fTicks);

	phasesPerTick = phases / fTicks;
}

static void setWavetable(int8* value) {
	wavetable = value;
}

static uint16 tick() {
	if (wavetable == NULL) {
		return 0;
	}

	if (tickCount >= ticks) {
		tickCount = 0;
	}

	uint16 phase = round(tickCount * phasesPerTick);
	int16 result =  wavetable[phase] * factor;

	tickCount++;

	return result;
}
};

int8* Lfo::wavetable;
uint16 Lfo::tickCount;
uint16 Lfo::ticks;
float Lfo::phasesPerTick;
float Lfo::frequency;
float Lfo::factor;

#endif
