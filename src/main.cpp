#include "wavetable.h"

HardwareTimer timer(1);

uint32 tickCount = 0;
bool ledState = false;

void tick() {
	if (tickCount == ticks_per_second) {
		tickCount = 0;
	}

	if (tickCount == 0) {
		digitalWrite(pin_led, ledState ? HIGH : LOW);
		ledState = !ledState;
	}

	tickCount++;
}

void setup() {
	pinMode(pin_led, OUTPUT);

	for (int i = 0; i < bits; i++) {
		pinMode(pins[i], OUTPUT);
	}

	calculateWavetable();

	timer.pause();
	timer.setPeriod(1e6 / ticks_per_second);
	timer.attachCompare1Interrupt(tick);
	timer.refresh();
	timer.resume();
}

void loop() {

}
