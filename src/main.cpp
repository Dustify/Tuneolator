#include <Arduino.h>
#include "config.h"
#include "wavetable.h"
#include "control.h"
//#include "demo.h"
#include "led.h"
#include "midi.h"

HardwareTimer timer(1);

void tick() {
	Led::tick();
	Control::tick();
}

void setup() {
	Led::init();
	Midi::init();

	timer.pause();
	timer.setPeriod(1e6 / ticks_per_second);
	timer.attachCompare1Interrupt(tick);
	timer.refresh();
	timer.resume();

	Lfo::setWavetable(Wavetable::sine);
	Wavetable::setSplit(0);
	Wavetable::setLow(Wavetable::triangle);
	Wavetable::setHigh(Wavetable::sawtooth);
}

void loop() {
		Midi::process();
}
