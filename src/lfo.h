#include <Arduino.h>
#include "note.h"
#include "config.h"

// TODO: refactor config so it is passed in init or changed as var?
class Lfo {
public:
	static int8* wavetable;
	static Note note;

	static void init() {
		note.init(lfoFrequency);
	}

	static void setWavetable(int8* value) {
		wavetable = value;
	}

	static uint16 tick() {
		if (wavetable == NULL) {
			return 0;
		}

		uint16 phase = note.tick();

		return wavetable[phase] * lfoFactor;
	}
};

Note Lfo::note;
int8* Lfo::wavetable = NULL;
