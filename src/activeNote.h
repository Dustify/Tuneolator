#ifndef ACTIVENOTE_H
#define ACTIVENOTE_H

#include <Arduino.h>
#include "notes.h"
#include "wavetable.h"
#include "led.h"

const uint8 velocityDivisors[] = { 127,         127,    64,     43,     32,     26,     21,     18,     16,     14,     13,     12,     11,     10,     9,      9,      8,      8,      7,      7,      6,      6,      6,      6,      5,      5,      5,      5,      5,      4,      4,      4,      4,      4,      4,      4,      4,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1 };

class ActiveNote {
public:

static uint32 attackTicksPerIncrement;
static uint32 releaseTicksPerIncrement;

static uint32 getTicksPerIncrement(uint8 value, uint16 maxMilliseconds) {
	if (value == 0) {
		return 0;
	}

	float factor = value / 127.0;
	float ms = factor * maxMilliseconds;
	float ticks = (ms * ticks_per_second) / 1000.0;
	return round(ticks / 127.0);
}

static void setAttack(uint8 value) {
	attackTicksPerIncrement = getTicksPerIncrement(value, maxAttackMilliseconds);
}

static void setRelease(uint8 value) {
	releaseTicksPerIncrement = getTicksPerIncrement(value, maxReleaseMilliseconds);
}

uint32 envelopeCounter;
uint8 envelopePhase; // 0 attack 1 decay 2 sustain 3 release

bool active;
uint8 note;
uint8 velocityDivisor;

void init() {
	active = false;
}

// TODO: start note at same amplitude as last one
void start(uint8 note, uint8 velocity) {
	Led::indicate();
	ActiveNote::note = note;
	velocityDivisor = velocityDivisors[velocity];

	envelopePhase = 0;
	envelopeCounter = 0;
	active = true;
}

void stop() {
	envelopeCounter = 0;
	envelopePhase = 3;
}

static uint16 envelopeDivisor;

void processRelease() {
	if (ActiveNote::releaseTicksPerIncrement == 0) {
		envelopeDivisor = 127;
	} else {
		envelopeDivisor = (envelopeCounter / ActiveNote::releaseTicksPerIncrement) + 1;
	}

	if (envelopeDivisor >= 127) {
		active = false;
	}

	envelopeCounter++;
}

int16 tick() {
	uint16 phase = Notes::notes[note].tick();
	int16 amplitude = note < Wavetable::split ? Wavetable::currentLow[phase] : Wavetable::currentHigh[phase];

	envelopeDivisor = 1;

	// TODO: attack here
	// TODO: decay here
	// TODO: sustain here

	switch (envelopePhase) {
	case 3: processRelease(); break;
	}

	return (amplitude / velocityDivisor) / envelopeDivisor;
}
};

uint32 ActiveNote::attackTicksPerIncrement;
uint32 ActiveNote::releaseTicksPerIncrement;
uint16 ActiveNote::envelopeDivisor;

#endif
