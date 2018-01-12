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

	Control::playNote(60);
	Control::playNote(64);
	Control::playNote(67);
	//Control::playNote(72);
	//Control::playNote(76);

	while(1);
	// delay(1000);
	// Control::playNote(64);
	// delay(1000);
	// Control::playNote(67);
	// delay(1000);
  //
	// Control::stopNote(67);
	// delay(1000);
	// Control::stopNote(64);
	// delay(1000);
	// Control::stopNote(60);
	// delay(1000);

	//Demo::cycleNotes();

	//Demo::cycleTunes();
}
