#include "wavetable.h"

HardwareTimer timer(1);

uint tickCount = 0;
uint halfTicksPerSecond = ticks_per_second * 0.5;

void tick() {
	if (tickCount == ticks_per_second) {
		tickCount = 0;
	}

	if (tickCount == 0) {
		digitalWrite(pin_led, LOW);
	}

	if (tickCount == halfTicksPerSecond) {
		digitalWrite(pin_led, HIGH);
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
