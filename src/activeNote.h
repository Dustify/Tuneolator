#ifndef ACTIVENOTE_H
#define ACTIVENOTE_H

#include <Arduino.h>
#include "notes.h"
#include "wavetable.h"
#include "led.h"
#include "fixed.h"

const uint8 velocityDivisors[] = { 127,         127,    64,     43,     32,     26,     21,     18,     16,     14,     13,     12,     11,     10,     9,      9,      8,      8,      7,      7,      6,      6,      6,      6,      5,      5,      5,      5,      5,      4,      4,      4,      4,      4,      4,      4,      4,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1 };

class ActiveNote {
public:

static uint32 attackTicks;
static uint32 releaseTicks;

static uint32 getEnvelopeTicks(uint8 value, uint16 maxMilliseconds) {
	if (value == 0) {
		return 0;
	}

	float factor = value / 127.0;
	float ms = factor * maxMilliseconds;

	return round((ms * ticks_per_second) / 1000.0);
}

static void setAttack(uint8 value) {
	attackTicks = getEnvelopeTicks(value, maxAttackMilliseconds);
}

static void setRelease(uint8 value) {
	releaseTicks = getEnvelopeTicks(value, maxReleaseMilliseconds);
}

bool active;
uint8 note;
uint8 velocity;

void init() {
	active = false;
}

// TODO: start note at same amplitude as last one
void start(uint8 note, uint8 velocity) {
	Led::indicate();
	ActiveNote::note = note;
	ActiveNote::velocity = velocity;

	envelopePhase = 0;
	envelopeCounter = 0;
	active = true;
}

void stop() {
	// TODO: release needs to pick up from current position (i.e. pay attention to where attack / decay / sustain is)!
	envelopeCounter = 0;
	envelopePhase = 3;
}

int8 amplitude;
uint32 envelopeCounter;
uint8 envelopePhase; // 0 attack 1 decay 2 sustain 3 release

void processAttack() {
	if (envelopeCounter == attackTicks) {
		// we've finished attack, move to next envelope and reset counter
		envelopePhase++;
		envelopeCounter = 0;
		return;
	}

	amplitude = Fixed::factor(amplitude, envelopeCounter, attackTicks);

	envelopeCounter++;
}

void processRelease() {
	if (envelopeCounter == releaseTicks) {
		active = false;
		return;
	}

	amplitude = amplitude - Fixed::factor(amplitude, envelopeCounter, releaseTicks);

	envelopeCounter++;
}

int8 tick() {
	if (!active) {
		return 0;
	}

	uint16 phase = Notes::notes[note].tick();
	amplitude = note < Wavetable::split ? Wavetable::low[phase] : Wavetable::high[phase];

	// TODO: add more envelopes!
	switch (envelopePhase) {
	case 0: processAttack(); break;
	case 3: processRelease(); break;
	}

	return Fixed::factor(amplitude, velocity, 127);    // / velocityDivisor;
}
};

uint32 ActiveNote::attackTicks;
uint32 ActiveNote::releaseTicks;

#endif
