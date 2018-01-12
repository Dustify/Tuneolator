#include "control.h"
#define DEMO_TIMING 250

class Demo {
private:
  static void pause(float duration) {
    delay(DEMO_TIMING * duration);
  }

  static void playNote(uint8 note, float duration) {
    Control::playNote(note);
    pause(duration);
    Control::stopNote(note);
  }

public:
static void cycleNotes() {
	for (int i = 0; i < 128; i++) {
		playNote(i, 1);
	}

	for (int i = 126; i > 0; i--) {
		playNote(i, 1);
	}
}

static void vangelis() {
	playNote(67, 2);
	playNote(69, 2);
	playNote(64, 2);
	playNote(62, 4);
	pause(2);

	playNote(67, 3);
	playNote(69, 1);
	playNote(72, 4);
	pause(2);

	playNote(71, 0.5);
	playNote(69, 0.5);
	playNote(71, 4);
}

static void numan() {
	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);
	pause(1);

	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);
	pause(1);

	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);
	pause(1);

	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);

	playNote(64, 1);
	playNote(65, 1);
	pause(0.75);
	playNote(69, 1);
	playNote(65, 1);
	pause(2);

	playNote(64, 1);
	playNote(65, 0.9);
	pause(0.1);
	playNote(65, 0.9);
	playNote(69, 1);
	playNote(65, 1);
}

static void cycleTunes() {
	vangelis();
	pause(8);
	numan();
	pause(8);
}
};
