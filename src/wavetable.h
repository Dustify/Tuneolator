#include "config.h"
#include "math.h"

byte sine[phases] = {};

void calculateWavetable() {
	double halfAmplitudes = 255 / 2;
	double radiansPerPhase = (2 * PI) / phases;

	for (uint32 i = 0; i < phases; i++) {
		double value = sin(i * radiansPerPhase);
		value = value * halfAmplitudes;
		value += halfAmplitudes;

		sine[i] = round(value);
	}
}
