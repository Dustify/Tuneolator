#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

#define ENABLE_ENV_SMOOTH
#define ENABLE_DECAY_SUSTAIN

HardwareSerial &MidiSerial = Serial1;

const double ticks_per_second = 50e3;
const uint16_t phases = 8.1e3;

const float maxLfoFrequency = 10;

const uint16_t maxAttackMilliseconds = 1000;
const uint16_t maxDecayMilliseconds = 1000;
const uint16_t maxReleaseMilliseconds = 1500;

const uint8_t midiChannel = 2;

const uint8_t controlAttack = 14;

#ifdef ENABLE_DECAY_SUSTAIN
const uint8_t controlDecay = 15;
const uint8_t controlSustain = 16;
#endif

const uint8_t controlRelease = 17;

const uint8_t controlLfoWavetable = 12;
const uint8_t controlLfoFrequency = 95;
const uint8_t controlLfoFactor = 102;

const uint8_t controlLowWavetable = 18;
const uint8_t controlSplit = 73;
const uint8_t controlHighWavetable = 72;

const uint8_t controlVolume = 74;

// actual constants, not really configurable
const uint8_t polyphony = 9;
const uint8_t amplitudes = 254;
const uint8_t midiMaxValue = 127;

#endif
