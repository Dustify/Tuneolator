#ifndef NOTES_H
#define NOTES_H

#include <Arduino.h>
#include "note.h"

class Notes {
private:
public:
  static Note* notes;
  static void init() {
    for(uint8 i = 0; i < 128; i++) {
      notes[i].init(frequencies[i]);
    }
  }
};

Note* Notes::notes = new Note[128];

#endif
