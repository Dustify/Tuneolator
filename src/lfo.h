#include <Arduino.h>
#include "config.h"

// TODO: as this is just like playing a note, could we get away with treating it as such?
// TODO: refactor 'factor' config so it is passed in init / var
class Lfo {
public:
static double ticksPerWave;
static double phasesPerTick;
static uint32 tickCount;
static int8 *wavetable;

static void setWavetable(int8 *value) {
	wavetable = value;
}

static int16 tick() {
	if (wavetable == NULL) {
		return 0;
	}

	if (tickCount == ticksPerWave) {
		tickCount = 0;
	}

	uint32 phase = phasesPerTick * tickCount;
	uint16 result = wavetable[phase] * lfoFactor;

	tickCount++;

	return result;
}
};

int8* Lfo::wavetable = NULL;
double Lfo::ticksPerWave = ticks_per_second / lfoFrequency;
double Lfo::phasesPerTick = phases / ticksPerWave;
uint32 Lfo::tickCount  = 0;
