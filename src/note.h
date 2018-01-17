#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include "config.h"
#include "frequencies.h"
#include "fixed.h"

class Note {
public:
  uint16 ticks;
  uint16 tickCount;

  void init(double frequency) {
    ticks = round(ticks_per_second / frequency);
  }

  uint16 tick() {
    if (tickCount >= ticks) {
      tickCount = 0;
    }

    uint16 result = Fixed::factorNote(phases, tickCount, ticks);

    tickCount++;

    return result;
  }
};

#endif
