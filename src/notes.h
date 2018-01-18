#ifndef NOTES_H
#define NOTES_H

#include <Arduino.h>
#include "note.h"

class Notes {
private:
public:
  static Note notes[128];
  static void init() {
    for(uint8_t i = 0; i < 128; i++) {
      notes[i].init(frequencies[i]);
    }
  }
};

Note Notes::notes[128];

#endif
