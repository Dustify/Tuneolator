#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

const uint32_t ticks_per_second = 48e3;
const uint16_t phases = 7400;

const float maxLfoFrequency = 20;

const uint16_t maxAttackMilliseconds = 2000;
const uint16_t maxDecayMilliseconds = 2000;
const uint16_t maxReleaseMilliseconds = 5000;

const uint8_t midiChannel = 0;

const uint8_t controlAttack = 14;
const uint8_t controlDecay = 15;
const uint8_t controlSustain = 16;
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
