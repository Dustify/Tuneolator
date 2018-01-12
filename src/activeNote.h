#ifndef ACTIVENOTE_H
#define ACTIVENOTE_H

#include <Arduino.h>
#include "notes.h"
#include "wavetable.h"
#include "led.h"

const uint8 velocities[] = { 0, 	128, 	64, 	43, 	32, 	26, 	21, 	18, 	16, 	14, 	13, 	12, 	11, 	10, 	9, 	9, 	8, 	8, 	7, 	7, 	6, 	6, 	6, 	6, 	5, 	5, 	5, 	5, 	5, 	4, 	4, 	4, 	4, 	4, 	4, 	4, 	4, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	3, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1,	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1 };

class ActiveNote {
private:

public:
  bool active;
  uint8 note;
  uint8 velocityDivisor;

  void init() {
    active = false;
  }

  // TODO: start note at same amplitude as last one
  void start(uint8 note, uint8 velocity) {
    Led::indicate();
    ActiveNote::note = note;
    ActiveNote::velocityDivisor = velocities[velocity];
    active = true;
  }

  void stop() {
    active = false;
  }

  int16 tick() {
    uint16 phase = Notes::notes[note].tick();
    int16 amplitude = note < Wavetable::split ? Wavetable::currentLow[phase] :Wavetable::currentHigh[phase];

    // TODO: apply adsr here

    return amplitude / velocityDivisor;
  }
};

#endif
