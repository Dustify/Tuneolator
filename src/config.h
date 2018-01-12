#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

const uint32 ticks_per_second = 48e3;
const uint16 phases = 5e3;

const float lfoFrequency = 5;
const float lfoFactor = 0.5;

const uint8 polyphony = 10;

#endif
