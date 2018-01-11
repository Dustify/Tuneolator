#include <Arduino.h>
#include "config.h"
#include "wavetable.h"
#include "notes.h"
#include "control.h"
#include "lfo.h"
#include "demo.h"
#include "led.h"

HardwareTimer timer(1);

int8 *wavetable = NULL;

void tick() {
	Led::tick();

	int16 result = 0;

	for (uint8 i = 0; i < polyphony; i++) {
		uint8 activeNote = Control::activeNotes[i];

		if (activeNote == -1) {
			continue;
		}

		int16 phase = Notes::notes[activeNote].tick();

		result += wavetable[phase];
	}

	// TODO: performance :(
	//result += Lfo::tick();

	result += Wavetable::halfAmplitudes;

	result = result > 255 ? 255 : result;
	result = result < 0 ? 0 : result;

	GPIOA->regs->ODR = result;
}

void setup() {
	GPIOA->regs->CRL = 0x33333333;

	Notes::init();
	Wavetable::init();
	Led::init();
	Control::init();

	timer.pause();
	timer.setPeriod(1e6 / ticks_per_second);
	timer.attachCompare1Interrupt(tick);
	timer.refresh();
	timer.resume();
}

void loop() {
	wavetable = Wavetable::sine;

	//Control::playNote(60, 0);

	//Demo::cycleNotes();
}
