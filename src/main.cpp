#include <Arduino.h>
#include "notes.h"

#define TICKS_PER_SECOND 192e3

HardwareTimer fastTimer(1);

const uint8 pins[] = { PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7 };
//const uint8 pins[] = { PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0 };

void fastTick() {

}

void setup() {
	//pinMode(PIN_OUT, OUTPUT);

	fastTimer.pause();
	fastTimer.setPeriod(1e6 / TICKS_PER_SECOND);
	fastTimer.attachCompare1Interrupt(fastTick);
	fastTimer.refresh();
	fastTimer.resume();


}

void loop() {

}
