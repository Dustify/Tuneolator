#include "wavetable.h"
#include "notes.h"

HardwareTimer timer(1);

uint32 tickCount = 0;
bool ledState = false;

double ticksPerWave = 0;
double phasesPerTick = 0;
uint32 waveTickCount = 0;

byte *wavetable = sine;

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

	GPIOA->regs->ODR = wavetable[phase];

	waveTickCount++;

	tickCount++;
}

void playNote(double frequency) {
	phasesPerTick = 0;
	ticksPerWave = 0;
	waveTickCount = 0;

	if (frequency == 0) {
		return;
	}

	ticksPerWave = ticks_per_second / frequency;
	phasesPerTick = phases / ticksPerWave;
}

void pause(double duration) {
	delay(250 * duration);
}

void playNote(uint16 note, double duration) {
	playNote(notes[note]);
	pause(duration);
	playNote(0);
}

void setup() {
	pinMode(pin_led, OUTPUT);

	GPIOA->regs->CRL = 0x33333333;

	calculateWavetables();

	timer.pause();
	timer.setPeriod(1e6 / ticks_per_second);
	timer.attachCompare1Interrupt(tick);
	timer.refresh();
	timer.resume();
}

void cycleNotes() {
	for (int i = 0; i < 128; i++) {
		playNote(notes[i]);
		delay(250);
	}

	for (int i = 126; i > 0; i--) {
		playNote(notes[i]);
		delay(250);
	}
}

void vangelis() {
	playNote(67, 2);
	playNote(69, 2);
	playNote(64, 2);
	playNote(62, 4);
	pause(2);

	playNote(67, 3);
	playNote(69, 1);
	playNote(72, 4);
	pause(2);

	playNote(71, 0.5);
	playNote(69, 0.5);
	playNote(71, 4);
}

void numan() {
	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);
	pause(1);

	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);
	pause(1);

	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);
	pause(1);

	playNote(72, 1);
	playNote(71, 1);
	playNote(65, 1);
	playNote(67, 1);
	pause(1);
	playNote(67, 0.5);
	pause(0.5);
	playNote(67, 1);

	playNote(64, 1);
	playNote(65, 1);
	pause(0.75);
	playNote(69, 1);
	playNote(65, 1);
	pause(2);

	playNote(64, 1);
	playNote(65, 0.9);
	pause(0.1);
	playNote(65, 0.9);
	playNote(69, 1);
	playNote(65, 1);
}

void cycleTunes() {
	vangelis();
	pause(8);
	numan();
	pause(8);
}

void loop() {
	wavetable = sine;
	cycleTunes();

	wavetable = sawtooth;
	cycleTunes();
}
