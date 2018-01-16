#ifndef LFO_H
#define LFO_H

#include <Arduino.h>
#include "note.h"
#include "config.h"
#include "wavetable.h"

class Lfo {
public:
static int8* wavetable;
static uint32 tickCount;
static uint32 ticksPerWave;
static float phasesPerTick;
static float factor;

static void setWavetable(uint8 value) {
	if (value < 42) {
		wavetable = NULL;
		return;
	}

	if (value < 84) {
		wavetable = Wavetable::currentLow;
		return;
	}

	wavetable = Wavetable::currentHigh;
}

static void setFrequency(uint8 value) {
	float frequency = (value / 127.0) * maxLfoFrequency;
	float fTicksPerWave = ticks_per_second / frequency;
	ticksPerWave = round(fTicksPerWave);
	phasesPerTick = phases / fTicksPerWave;
}

static void setFactor(uint8 value) {
	factor = value / 127.0;
}

static uint16 tick() {
	if (wavetable == NULL) {
		return 0;
	}

	if (tickCount >= ticksPerWave) {
		tickCount = 0;
	}

	uint16 phase = round(tickCount * phasesPerTick);
	int16 result =  wavetable[phase] * factor;

	tickCount++;

	return result;
}
};

int8* Lfo::wavetable;
uint32 Lfo::tickCount;
uint32 Lfo::ticksPerWave;
float Lfo::phasesPerTick;
float Lfo::factor;

#endif
