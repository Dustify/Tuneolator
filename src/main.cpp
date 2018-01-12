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
	//Lfo::setWavetable(Wavetable::sine);
	Control::setWavetable(Wavetable::sine);

	//Demo::cycleTunes();

	Control::playNote(36);
	Control::playNote(40);
	Control::playNote(43);

	Control::playNote(48);
	Control::playNote(52);
	Control::playNote(55);

	Control::playNote(60);
	Control::playNote(64);
	Control::playNote(67);

	Control::playNote(72);

	while(1);
}
