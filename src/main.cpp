#include <Arduino.h>
#include "config.h"
#include "wavetable.h"
#include "control.h"
#include "demo.h"
#include "led.h"

HardwareTimer timer(1);

void tick() {
	Led::tick();
	Control::tick();
}

void setup() {
	Control::init();
	Led::init();

	timer.pause();
	timer.setPeriod(1e6 / ticks_per_second);
	timer.attachCompare1Interrupt(tick);
	timer.refresh();
	timer.resume();
}

void loop() {
	// TODO: fix lfo
	//Lfo::setWavetable(Wavetable::sine);

	Control::setWavetable(Wavetable::sine);
	Control::playNote(60);
	delay(2500);

	Control::setWavetable(Wavetable::sawtooth);
	delay(2500);

	Control::setWavetable(Wavetable::triangle);
	delay(2500);
	Control::stopNote(60);

	Control::setWavetable(Wavetable::sawtooth);

	while (1) {
		for (uint8 i = 0; i < 12; i++) {
			Demo::chords(36 + i);
		}
	}
}
