#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include "config.h"
#include "frequencies.h"
#include "fixed.h"

class Note {
public:
  uint16_t ticks;
  uint16_t tickCount;

  void init(double frequency) {
    ticks = round(ticks_per_second / frequency);
  }

  uint16_t tick() {
    if (tickCount >= ticks) {
      tickCount = 0;
    }

    uint16_t result = Fixed::factorNote(phases, tickCount, ticks);

    tickCount++;

    return result;
  }
};

#endif
