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
	Lfo::setWavetable(Wavetable::sine);
	Control::setWavetable(Wavetable::sine);

	Demo::cycleTunes();
}
