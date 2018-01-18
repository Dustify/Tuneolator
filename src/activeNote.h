#ifndef ACTIVENOTE_H
#define ACTIVENOTE_H

#include <Arduino.h>
#include "notes.h"
#include "wavetable.h"
#include "led.h"
#include "fixed.h"
#include "config.h"

class ActiveNote {
public:

static uint32 attackTicks;
static uint32 decayTicks;
static uint8 sustainLevel;
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

static void setDecay(uint8 value) {
	decayTicks = getEnvelopeTicks(value, maxDecayMilliseconds);
}

static void setSustain(uint8 value) {
	sustainLevel = value;
}

static void setRelease(uint8 value) {
	releaseTicks = getEnvelopeTicks(value, maxReleaseMilliseconds);
}

bool active;
bool available;
uint8 note;
uint8 velocity;

void init() {
	active = false;
	available = true;
}

// TODO: start note at same amplitude as last one
void start(uint8 note, uint8 velocity) {
	Led::indicate();
	ActiveNote::note = note;
	ActiveNote::velocity = velocity;

	envelopePhase = 0;
	envelopeCounter = 0;
	active = true;
	available = false;
}

void stop() {
	// TODO: release needs to pick up from current position (i.e. pay attention to where attack / decay / sustain is)!
	envelopeCounter = 0;
	envelopePhase = 3;
	available = true;
}

int8 amplitude;
uint32 envelopeCounter;
uint8 envelopePhase; // 0 attack 1 decay 2 sustain 3 release

void processAttack() {
	if (envelopeCounter >= attackTicks) {
		// we've finished attack, move to next envelope and reset counter
		envelopePhase++;
		envelopeCounter = 0;
		return;
	}

	amplitude = Fixed::factorEnvelope(amplitude, envelopeCounter, attackTicks);

	envelopeCounter++;
}

void processDecay() {
	if (envelopeCounter >= decayTicks) {
		envelopePhase++;
		envelopeCounter = 0;
		return;
	}

	envelopeCounter++;
}

void processSustain() {
}

void processRelease() {
	if (envelopeCounter >= releaseTicks) {
		active = false;
		return;
	}

	amplitude = amplitude - Fixed::factorEnvelope(amplitude, envelopeCounter, releaseTicks);

	envelopeCounter++;
}

int8 tick() {
	if (!active || Wavetable::busy) {
		return 0;
	}

	uint16 phase = Notes::notes[note].tick();
	amplitude = note < Wavetable::split ? Wavetable::low[phase] : Wavetable::high[phase];

	// TODO: add more envelopes!
	switch (envelopePhase) {
	case 0: processAttack(); break;
	case 1: processDecay(); break;
	case 2: processSustain(); break;
	case 3: processRelease(); break;
	}

	return Fixed::factorVelocity(amplitude, velocity, midiMaxValue);
}
};

uint32 ActiveNote::attackTicks;
uint32 ActiveNote::decayTicks;
uint8 ActiveNote::sustainLevel;
uint32 ActiveNote::releaseTicks;

#endif
