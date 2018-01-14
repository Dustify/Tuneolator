#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include "config.h"
#include "frequencies.h"

class Note {
public:
  uint16 ticks;
  uint16 phasesPerTick;
  uint16 tickCount;

  void init(float frequency) {
    float fTicks = ticks_per_second / frequency;

    ticks = round(fTicks);
    phasesPerTick = round(phases / fTicks);
  }

  int16 tick() {
    if (tickCount >= ticks) {
      tickCount = 0;
    }

    int16 result = tickCount * phasesPerTick;

    tickCount++;

    return result;
  }


};

#endif
