#include <Arduino.h>
#include "config.h"

class Wavetable {
public:
	static int8 sine[phases];
	static int8 sawtooth[phases];
	static int8 triangle[phases];

	static uint16 amplitudes;
	static double halfAmplitudes;

	static void init() {
		double radiansPerPhase = (2 * PI) / phases;
		double amplitudesPerPhase = (double)amplitudes / (double)phases;

		uint32 halfPhases = round(phases * 0.5);

		double amplitudesPerHalfPhase = amplitudes / halfPhases;

		for (uint32 i = 0; i < phases; i++) {
			// sine
			double sineValue = sin(i * radiansPerPhase);
			sineValue = sineValue * halfAmplitudes;

			sine[i] = round(sineValue);

			// sawtooth
			sawtooth[i] = round(i * amplitudesPerPhase - halfAmplitudes);

			// triangle
			if (i < halfPhases) {
				triangle[i] = round(i * amplitudesPerHalfPhase - halfAmplitudes);
			} else {
				triangle[i] = round(amplitudes - ((i - halfPhases) * amplitudesPerHalfPhase) - halfAmplitudes);
			}
		}
	}
};

int8 Wavetable::sine[phases] = {};
int8 Wavetable::sawtooth[phases] = {};
int8 Wavetable::triangle[phases] = {};

uint16 Wavetable::amplitudes = 255;
double Wavetable::halfAmplitudes = amplitudes / 2;
