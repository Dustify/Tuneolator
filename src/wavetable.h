#ifndef WAVETABLE_H
#define WAVETABLE_H

#include <Arduino.h>
#include "config.h"

class Wavetable {
public:
	static int8 sine[phases];
	static int8 sawtooth[phases];
	static int8 triangle[phases];

	static int8* currentLow;
	static int8* currentHigh;
	static uint8 split;

	static uint16 amplitudes;
	static float halfAmplitudes;

	static void init() {
		float radiansPerPhase = (2 * PI) / phases;
		float amplitudesPerPhase = (float)amplitudes / (float)phases;

		uint16 halfPhases = round(phases * 0.5);

		float amplitudesPerHalfPhase = amplitudes / halfPhases;

		for (uint16 i = 0; i < phases; i++) {
			// sine
			float sineValue = sin(i * radiansPerPhase);
			sineValue = sineValue * halfAmplitudes;

			sine[i] = round(sineValue);

			// sawtooth
			sawtooth[i] = round(i * amplitudesPerPhase - halfAmplitudes);

			// triangle
			float triangleAmplitude = i * amplitudesPerHalfPhase - halfAmplitudes;

			if (i < halfPhases) {
				triangle[i] = round(triangleAmplitude);
			} else {
				triangle[i] = round(amplitudes - triangleAmplitude);
			}
		}
	}

	static void setLow(int8* value) {
		currentLow = value;
	}

	static void setHigh(int8* value) {
		currentHigh = value;
	}

	static void setSplit(uint8 value) {
		split = value;
	}
};

int8 Wavetable::sine[phases] = {};
int8 Wavetable::sawtooth[phases] = {};
int8 Wavetable::triangle[phases] = {};

int8* Wavetable::currentLow;
int8* Wavetable::currentHigh;
uint8 Wavetable::split;

uint16 Wavetable::amplitudes = 255;
float Wavetable::halfAmplitudes = amplitudes / 2;

#endif
