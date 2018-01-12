#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include "frequencies.h"

class Note {
public:
void init(float frequency);
int16 tick();
uint16 ticks;
float phasesPerTick;
uint16 tickCount;
};

#endif
