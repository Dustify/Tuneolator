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

static uint32_t attackTicks;
#ifdef ENABLE_DECAY_SUSTAIN
static uint32_t decayTicks;
static uint8_t sustainLevel;
#endif
static uint32_t releaseTicks;

static uint32_t getEnvelopeTicks(uint8_t value, uint16_t maxMilliseconds) {
	if (value == 0) {
		return 0;
	}

	float factor = value / 127.0;
	float ms = factor * maxMilliseconds;

	return round((ms * ticks_per_second) / 1000.0);
}

static void setAttack(uint8_t value) {
	attackTicks = getEnvelopeTicks(value, maxAttackMilliseconds);
}

#ifdef ENABLE_DECAY_SUSTAIN
static void setDecay(uint8_t value) {
	decayTicks = getEnvelopeTicks(value, maxDecayMilliseconds);
}

static void setSustain(uint8_t value) {
	sustainLevel = value;
}
#endif

static void setRelease(uint8_t value) {
	releaseTicks = getEnvelopeTicks(value, maxReleaseMilliseconds);
}

bool active;
bool available;
uint8_t note;
uint8_t velocity;

void init() {
	active = false;
	available = true;
}

// TODO: start note at same amplitude as last one
void start(uint8_t note, uint8_t velocity) {
	Led::indicate();
	ActiveNote::note = note;
	ActiveNote::velocity = velocity;

	envelopePhase = 0;
	envelopeCounter = 0;
	active = true;
	available = false;
}

void stop() {
	envelopeCounter = 0;
	envelopePhase = 3;
	available = true;
}

int8_t amplitude;
uint32_t envelopeCounter;
uint8_t envelopePhase; // 0 attack 1 decay 2 sustain 3 release

#ifdef ENABLE_ENV_SMOOTH
// store last used factor values for release
uint32_t envelopeNumerator;
uint32_t envelopeDenominator;
#endif

void processAttack() {
	if (envelopeCounter >= attackTicks) {
		// we've finished attack, move to next envelope and reset counter
		envelopePhase++;
		envelopeCounter = 0;
		return;
	}

	amplitude = Fixed::factorEnvelope(amplitude, envelopeCounter, attackTicks);

	#ifdef ENABLE_ENV_SMOOTH
	envelopeNumerator = envelopeCounter;
	envelopeDenominator = attackTicks;
	#endif

	envelopeCounter++;
}

#ifdef ENABLE_DECAY_SUSTAIN
void processDecay() {
	if (envelopeCounter >= decayTicks) {
		envelopePhase++;
		envelopeCounter = 0;
		return;
	}

	uint8_t fullDecayDrop = 127 - sustainLevel;
	uint8_t decayDrop = 127 - Fixed::factorDecayDrop(fullDecayDrop, envelopeCounter, decayTicks);
	amplitude = Fixed::factorVelocity(amplitude, decayDrop, 127);

	#ifdef ENABLE_ENV_SMOOTH
	envelopeNumerator = decayDrop;
	envelopeDenominator = 127;
	#endif

	envelopeCounter++;
}

void processSustain() {
	amplitude = Fixed::factorVelocity(amplitude, sustainLevel, 127);

	#ifdef ENABLE_ENV_SMOOTH
	envelopeNumerator = sustainLevel;
	envelopeDenominator = 127;
	#endif
}
#endif

void processRelease() {
	if (envelopeCounter >= releaseTicks) {
		active = false;
		return;
	}

	#ifdef ENABLE_ENV_SMOOTH
	amplitude = Fixed::factorEnvelope(amplitude, envelopeNumerator, envelopeDenominator);
	#endif

	amplitude = amplitude - Fixed::factorEnvelope(amplitude, envelopeCounter, releaseTicks);

	envelopeCounter++;
}

int8_t tick() {
	if (!active || Wavetable::busy) {
		return 0;
	}

	uint16_t phase = Notes::notes[note].tick();
	amplitude = note < Wavetable::split ? Wavetable::low[phase] : Wavetable::high[phase];

	switch (envelopePhase) {
	case 0: processAttack(); break;
	#ifdef ENABLE_DECAY_SUSTAIN
	case 1: processDecay(); break;
	case 2: processSustain(); break;
	#endif
	case 3: processRelease(); break;
	}

	return Fixed::factorVelocity(amplitude, velocity, midiMaxValue);
}
};

uint32_t ActiveNote::attackTicks;
#ifdef ENABLE_DECAY_SUSTAIN
uint32_t ActiveNote::decayTicks;
uint8_t ActiveNote::sustainLevel = 127;
#endif
uint32_t ActiveNote::releaseTicks;

#endif
