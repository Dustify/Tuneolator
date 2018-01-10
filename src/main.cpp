#include "wavetable.h"
#include "notes.h"

HardwareTimer timer(1);

uint32 tickCount = 0;
bool ledState = false;

double ticksPerWave = 0;
double phasesPerTick = 0;
uint32 waveTickCount = 0;

void tick() {
	if (tickCount == ticks_per_second) {
		tickCount = 0;
	}

	if (tickCount == 0) {
		digitalWrite(pin_led, ledState ? HIGH : LOW);
		ledState = !ledState;
	}

	if (waveTickCount > ticksPerWave - 1) {
		waveTickCount = 0;
	}

	uint32 phase = waveTickCount * phasesPerTick;

	GPIOA->regs->ODR = sine[phase];

	waveTickCount++;

	tickCount++;
}

void playNote(double frequency) {
	phasesPerTick = 0;
	waveTickCount = 0;
	ticksPerWave = ticks_per_second / frequency;
	phasesPerTick = phases / ticksPerWave;
}

void setup() {
	pinMode(pin_led, OUTPUT);

	GPIOA->regs->CRL = 0x33333333;

	calculateWavetable();

	timer.pause();
	timer.setPeriod(1e6 / ticks_per_second);
	timer.attachCompare1Interrupt(tick);
	timer.refresh();
	timer.resume();
}

void loop() {
	for (int i = 0; i < 128; i++) {
		playNote(notes[i]);
		delay(250);
	}

	for (int i = 126; i > 0; i--) {
		playNote(notes[i]);
		delay(250);
	}
}
