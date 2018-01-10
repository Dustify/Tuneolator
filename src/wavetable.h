#include "config.h"
#include "math.h"

byte sine[phases] = {};
byte sawtooth[phases] = {};
byte triangle[phases] = {};

void calculateWavetables() {
	uint16 amplitudes = 255;
	double halfAmplitudes = amplitudes / 2;
	double radiansPerPhase = (2 * PI) / phases;
	double amplitudesPerPhase = (double)amplitudes / (double)phases;

	uint32 halfPhases = round(phases * 0.5);

	double amplitudesPerHalfPhase = amplitudes / halfPhases;

	for (uint32 i = 0; i < phases; i++) {
		// sine
		double sineValue = sin(i * radiansPerPhase);
		sineValue = sineValue * halfAmplitudes;
		sineValue += halfAmplitudes;

		sine[i] = round(sineValue);

		// sawtooth
		sawtooth[i] = round(i * amplitudesPerPhase);

		// triangle
		if (i < halfPhases) {
			triangle[i] = round(i * amplitudesPerHalfPhase);
		} else {
			triangle[i] = round(amplitudes - ((i - halfPhases) * amplitudesPerHalfPhase));
		}
	}
}
