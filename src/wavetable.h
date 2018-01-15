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

static uint8 halfAmplitudes;

static void init() {
	uint16 amplitudes = 254;
	double dHalfAmplitudes = amplitudes / 2;
	halfAmplitudes = round(dHalfAmplitudes);

	double radiansPerPhase = (2 * PI) / phases;
	double amplitudesPerPhase = (float)amplitudes / (float)phases;

	double quarterPhases = phases / 4;
	double amplitudesPerHalfPhase = amplitudesPerPhase * 2;

	for (uint16 i = 0; i < phases; i++) {
		// sine
		float sineValue = sin(i * radiansPerPhase);
		sineValue = sineValue * dHalfAmplitudes;

		sine[i] = round(sineValue);

		// sawtooth
		sawtooth[i] = round(i * amplitudesPerPhase - dHalfAmplitudes);

		// triangle
		float triangleAmplitude = i * amplitudesPerHalfPhase;
		uint8 quarterPhase = i / quarterPhases;

		if (quarterPhase == 0) {
			triangle[i] = round(triangleAmplitude);
		}

		if (quarterPhase > 0 && quarterPhase < 3) {
			triangle[i] = round(amplitudes - triangleAmplitude);
		}

		if (quarterPhase == 3) {
			triangle[i] = round(triangleAmplitude - (2 * amplitudes));
		}
	}
}

static void setLow(uint8 value) {
	if (value < 43) {
		currentLow = Wavetable::sine;
		return;
	}

	if (value < 86) {
		currentLow = Wavetable::triangle;
		return;
	}

	currentLow = Wavetable::sawtooth;
}

static void setHigh(uint8 value) {
	if (value < 43) {
		currentHigh = Wavetable::sine;
		return;
	}

	if (value < 86) {
		currentHigh = Wavetable::triangle;
		return;
	}

	currentHigh = Wavetable::sawtooth;
}

static void setSplit(uint8 value) {
	split = value;
}
};

int8 Wavetable::sine[phases] = {};
int8 Wavetable::sawtooth[phases] = {};
int8 Wavetable::triangle[phases] = {};

int8* Wavetable::currentLow = Wavetable::sine;
int8* Wavetable::currentHigh = Wavetable::sine;
uint8 Wavetable::split = 0;

uint8 Wavetable::halfAmplitudes;

#endif
