#include "config.h"
#include "math.h"

byte sine[phases] = {};
byte sawtooth[phases] = {};

void calculateWavetables() {
	uint16 amplitudes = 255;
	double halfAmplitudes = amplitudes / 2;
	double radiansPerPhase = (2 * PI) / phases;
	double amplitudesPerPhase = (double)amplitudes / (double)phases;

	for (uint32 i = 0; i < phases; i++) {
		// sine
		double sineValue = sin(i * radiansPerPhase);
		sineValue = sineValue * halfAmplitudes;
		sineValue += halfAmplitudes;

		sine[i] = round(sineValue);

		// sawtooth
		sawtooth[i] = round(i * amplitudesPerPhase);
	}
}
