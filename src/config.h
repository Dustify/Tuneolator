#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

const uint32 ticks_per_second = 48e3;
const uint16 phases = 5e3;

const uint8 polyphony = 10;

const uint16 maxAttackMilliseconds = 2000;
const uint16 maxDecayMilliseconds = 2000;
const uint16 maxReleaseMilliseconds = 5000;

const uint8 midiChannel = 0;

const uint8 controlAttack = 14;
const uint8 controlDecay = 15;
const uint8 controlSustain = 16;
const uint8 controlRelease = 17;

const uint8 controlLfoWavetable = 12;
const uint8 controlLfoFrequency = 95;
const uint8 controlLfoFactor = 102;

const uint8 controlLowWavetable = 18;
const uint8 controlSplit = 73;
const uint8 controlHighWavetable = 72;

#endif
