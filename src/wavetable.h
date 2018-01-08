#include "config.h"
#include "notes.h"
#include "math.h"

const uint8 bits = sizeof(pins) / sizeof(uint8);
const uint16 amplitudes = pow(2, bits);

uint8 sine[phases] = {};

void calculateWavetable() {
	uint16 halfAmplitudes = (amplitudes / 2) - 1;
	double radiansPerPhase = (2 * PI) / phases;

	for (uint32 i = 0; i < phases; i++) {
		double value = sin(i * radiansPerPhase);
		value = value * halfAmplitudes;
		value += halfAmplitudes;

		sine[i] = round(value);
	}
}
