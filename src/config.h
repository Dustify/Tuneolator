#include <Arduino.h>

const uint8 pin_led = PC13;
const uint32 ticks_per_second = 48e3;
const uint32 phases = 5e3;
const int voices = 3;
const double lfoFrequency = 1;
