#include <Arduino.h>
#include "note.h"
#include "config.h"

// TODO: refactor config so it is passed in init or changed as var?
class Lfo {
public:
static int8* wavetable;
static uint16 tickCount;
static uint16 ticks;
static float phasesPerTick;

static void init() {
	float fTicks = ticks_per_second / lfoFrequency;
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
	int16 result =  wavetable[phase] * lfoFactor;

	tickCount++;

	return result;
}
};

int8* Lfo::wavetable;
uint16 Lfo::tickCount;
uint16 Lfo::ticks;
float Lfo::phasesPerTick;
