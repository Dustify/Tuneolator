#ifndef ACTIVENOTE_H
#define ACTIVENOTE_H

#include <Arduino.h>
#include "notes.h"
#include "wavetable.h"
#include "led.h"

const uint8 velocityDivisors[] = { 128,         128,    64,     43,     32,     26,     21,     18,     16,     14,     13,     12,     11,     10,     9,      9,      8,      8,      7,      7,      6,      6,      6,      6,      5,      5,      5,      5,      5,      4,      4,      4,      4,      4,      4,      4,      4,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1 };

class ActiveNote {
public:


// static uint16 attackTicks;
// static uint16 decayTicks;
// static uint8 sustainLevel;
static uint32 releaseTicksPerIncrement;

static void setRelease(uint8 value) {
	float factor = value / 127.0;
	float ms = factor * maxReleaseMilliseconds;
	float ticks = (ms * ticks_per_second) / 1000.0;
	releaseTicksPerIncrement = ticks / 127.0;
}

uint32 envelopeCounter;
bool releaseActive;

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
	ActiveNote::velocityDivisor = velocityDivisors[velocity];
	releaseActive = false;
	active = true;
}

void stop() {
	envelopeCounter = 0;
	releaseActive = true;
}

int16 tick() {
	uint16 phase = Notes::notes[note].tick();
	int16 amplitude = note < Wavetable::split ? Wavetable::currentLow[phase] : Wavetable::currentHigh[phase];

	// TODO: apply adsr here

	uint16 envelopeDivisor = 1;

	if (releaseActive) {
		if (ActiveNote::releaseTicksPerIncrement == 0) {
			envelopeDivisor = 127;
		} else {
			envelopeDivisor = (envelopeCounter / ActiveNote::releaseTicksPerIncrement) + 1;
		}

		if (envelopeDivisor >= 127) {
			active = false;
      releaseActive = false;
		}

		envelopeCounter++;
	}

	return (amplitude / velocityDivisor) / envelopeDivisor;
}
};

uint32 ActiveNote::releaseTicksPerIncrement;

#endif
