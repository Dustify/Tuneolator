#include <Arduino.h>

const uint8 pin_led = PC13;
const uint32 ticks_per_second = 96e3;
const uint32 phases = 2000;
const uint8 pins[] = { PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7 };
//const uint8 pins[] = { PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0 };
