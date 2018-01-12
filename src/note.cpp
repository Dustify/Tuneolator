#include "config.h"
#include "note.h"

void Note::init(float frequency) {
  float fTicks = ticks_per_second / frequency;

  ticks = round(fTicks);
  phasesPerTick = round(phases / fTicks);
}

int16 Note::tick() {
  if (tickCount >= ticks) {
    tickCount = 0;
  }

  int16 result = tickCount * phasesPerTick;

  tickCount++;

  return result;
}
