#ifndef ACTIVENOTE_H
#define ACTIVENOTE_H

#include <Arduino.h>
#include "notes.h"
#include "wavetable.h"

class ActiveNote {
private:
public:
  bool active;
  uint8 note;

  void init() {
    active = false;
  }

  // TODO: add velocity
  // TODO: start note at same amplitude as last one
  void start(uint8 note) {
    ActiveNote::note = note;
    active = true;
  }

  void stop() {
    active = false;
  }

  int16 tick() {
    uint16 phase = Notes::notes[note].tick();
    int16 amplitude = Wavetable::current[phase];

    // apply adsr here

    return amplitude;
  }
};

#endif
