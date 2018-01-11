#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include "frequencies.h"

class Note {
public:
void init(double frequency);
int16 tick();
double frequency;
double ticks;
double phasesPerTick;
uint32 tickCount;
};

#endif
