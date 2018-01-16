#ifndef WAVETABLE_H
#define WAVETABLE_H

#include <Arduino.h>
#include "config.h"

class Wavetable {
public:

static int8 currentLow[phases];
static int8 currentHigh[phases];
static uint8 split;
static uint8 halfAmplitudes;

static void init() {
	double dHalfAmplitudes = amplitudes / 2;
	halfAmplitudes = round(dHalfAmplitudes);

	setSine(currentLow);
	setSine(currentHigh);
}

static void setSine(int8 *target) {
	double dHalfAmplitudes = amplitudes / 2.0;
	double radiansPerPhase = (2.0 * PI) / phases;

	for (uint16 i = 0; i < phases; i++) {
		// sine
		float sineValue = sin(i * radiansPerPhase);
		sineValue = sineValue * dHalfAmplitudes;

		target[i] = round(sineValue);
	}
}

static void setSawtooth(int8 *target) {
	double dHalfAmplitudes = amplitudes / 2.0;
	double amplitudesPerPhase = (float)amplitudes / (float)phases;

	for (uint16 i = 0; i < phases; i++) {
		target[i] = round(i * amplitudesPerPhase - dHalfAmplitudes);
	}
}

static void setTriangle(int8 *target) {
	double amplitudesPerPhase = (float)amplitudes / (float)phases;
	double quarterPhases = phases / 4.0;
	double amplitudesPerHalfPhase = amplitudesPerPhase * 2.0;

	for (uint16 i = 0; i < phases; i++) {
		float triangleAmplitude = i * amplitudesPerHalfPhase;
		uint8 quarterPhase = i / quarterPhases;

		if (quarterPhase == 0) {
			target[i] = round(triangleAmplitude);
		}

		if (quarterPhase > 0 && quarterPhase < 3.0) {
			target[i] = round(amplitudes - triangleAmplitude);
		}

		if (quarterPhase == 3.0) {
			target[i] = round(triangleAmplitude - (2.0 * amplitudes));
		}
	}
}

static void setSquare(int8 *target) {
	double halfPhases = phases / 2.0;

	for (uint16 i = 0; i < phases; i++) {
			target[i] = i < halfPhases ? 127 : -127;
	}
}

static void setTable(uint8 value, int8 *target) {
	if (value < 32) {
		setSine(target);
		return;
	}

	if (value < 64) {
		setTriangle(target);
		return;
	}

	if (value < 96) {
		setSquare(target);
		return;
	}

	setSawtooth(target);
}

static void setLow(uint8 value) {
	setTable(value, currentLow);
}

static void setHigh(uint8 value) {
	setTable(value, currentHigh);
}

static void setSplit(uint8 value) {
	split = value;
}
};

int8 Wavetable::currentLow[phases];
int8 Wavetable::currentHigh[phases];
uint8 Wavetable::split = 0;

uint8 Wavetable::halfAmplitudes;

#endif
