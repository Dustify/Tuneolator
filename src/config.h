#include <Arduino.h>

const uint8 pin_led = PC13;
const uint32 ticks_per_second = 96e3;
const uint32 phases = 11742; // ticks_per_second / 8.1757989156Hz
