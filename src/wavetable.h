#ifndef WAVETABLE_H
#define WAVETABLE_H

#include <Arduino.h>
#include "config.h"

class Wavetable {
public:

static bool busy;

static int8_t low[phases];
static int8_t high[phases];

static uint8_t split;
static uint8_t halfAmplitudes;

static void init() {
	double dHalfAmplitudes = amplitudes / 2;
	halfAmplitudes = round(dHalfAmplitudes);

	setSine(low);
	setSine(high);
}

static void setSine(int8_t *target) {
	busy = true;
	double dHalfAmplitudes = amplitudes / 2.0;
	double radiansPerPhase = (2.0 * PI) / phases;

	for (uint16_t i = 0; i < phases; i++) {
		float sineValue = sin(i * radiansPerPhase);
		sineValue = sineValue * dHalfAmplitudes;

		target[i] = round(sineValue);
	}

	busy = false;
}

static void setTriangle(int8_t *target) {
	busy = true;
	double amplitudesPerPhase = (float)amplitudes / (float)phases;
	double quarterPhases = phases / 4.0;
	double amplitudesPerHalfPhase = amplitudesPerPhase * 2.0;

	for (uint16_t i = 0; i < phases; i++) {
		float triangleAmplitude = i * amplitudesPerHalfPhase;
		uint8_t quarterPhase = i / quarterPhases;

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

	busy = false;
}

static void setSquare(int8_t *target) {
	busy = true;
	double halfPhases = phases / 2.0;

	for (uint16_t i = 0; i < phases; i++) {
		target[i] = i < halfPhases ? 127 : -127;
	}

	busy = false;
}

static void setSawtooth(int8_t *target) {
	busy = true;
	double dHalfAmplitudes = amplitudes / 2.0;
	double amplitudesPerPhase = (float)amplitudes / (float)phases;

	for (uint16_t i = 0; i < phases; i++) {
		target[i] = round(i * amplitudesPerPhase - dHalfAmplitudes);
	}

	busy = false;
}

static uint8_t low_wave_id;
static uint8_t high_wave_id;

static bool isTableAlreadySet(uint8_t table_id, uint8_t wave_id) {
	if (table_id == 0) {
		if (low_wave_id == wave_id) {
			return true;
		} else {
			low_wave_id = wave_id;
			return false;
		}
	} else if (table_id == 1) {
		if (high_wave_id == wave_id) {
			return true;
		} else {
			high_wave_id = wave_id;
			return false;
		}
	}

	return false;
}

static void setTable(uint8_t value, int8_t *target, uint8_t table_id) {
	if (value < 32) {
		if (isTableAlreadySet(table_id, 0)) {
			return;
		}

		setSine(target);
		return;
	}

	if (value < 64) {
		if (isTableAlreadySet(table_id, 1)) {
			return;
		}

		setTriangle(target);
		return;
	}

	if (value < 96) {
		if (isTableAlreadySet(table_id, 2)) {
			return;
		}

		setSquare(target);
		return;
	}

	if (isTableAlreadySet(table_id, 3)) {
		return;
	}

	setSawtooth(target);
}

static void setLow(uint8_t value) {
	setTable(value, low, 0);
}

static void setHigh(uint8_t value) {
	setTable(value, high, 1);
}

static void setSplit(uint8_t value) {
	split = value;
}
};

int8_t Wavetable::low[phases];
int8_t Wavetable::high[phases];
uint8_t Wavetable::split = 0;

uint8_t Wavetable::halfAmplitudes;

uint8_t Wavetable::low_wave_id;
uint8_t Wavetable::high_wave_id;

bool Wavetable::busy;

#endif
