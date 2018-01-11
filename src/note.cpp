#include "config.h"
#include "note.h"

void Note::init(double frequency) {
  Note::frequency = frequency;

  ticks = ticks_per_second / frequency;
  phasesPerTick = phases / ticks;
}

int16 Note::tick() {
  if (tickCount >= ticks) {
    tickCount = 0;
  }

  int16 result = tickCount * phasesPerTick;

  tickCount++;

  return result;
}
