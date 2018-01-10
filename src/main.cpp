#include "wavetable.h"
#include "note.h"

HardwareTimer timer(1);

uint32 tickCount = 0;
bool ledState = false;

double ticksPerWave = 0;
double phasesPerTick = 0;
uint32 waveTickCount = 0;

bool squareEnabled = false;
byte *wavetable[voices] = {};

byte *lfoWavetable = NULL;
double lfoTicksPerWave = ticks_per_second / lfoFrequency;
double lfoPhasesPerTick = phases / lfoTicksPerWave;
uint32 lfoWaveTickCount = 0;

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

	uint32 result = 0;

	for (int i = 0; i < voices; i++) {
		byte *voice = wavetable[i];

		if (voice != NULL) {
			result += voice[phase];
		}
	}

	if (squareEnabled && waveTickCount < ticksPerWave * 0.5) {
		result += 255;
	}

	// lfo
	if (lfoWaveTickCount == lfoTicksPerWave) {
		lfoWaveTickCount = 0;
	}

	if (lfoWavetable != NULL) {
		uint32 lfoPhase = lfoPhasesPerTick * lfoWaveTickCount;

		result += lfoWavetable[lfoPhase ];
	}

	result = result > 255 ? 255 : result;

	GPIOA->regs->ODR = result;

	lfoWaveTickCount++;
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
	lfoWavetable = sine;
	wavetable[0] = sine;
	wavetable[1] = NULL;
	wavetable[2] = NULL;
	squareEnabled = false;
	cycleTunes();

	lfoWavetable = NULL;
	wavetable[0] = NULL;
	wavetable[1] = NULL;
	wavetable[2] = NULL;
	squareEnabled = true;
	cycleTunes();

	lfoWavetable = NULL;
	wavetable[0] = triangle;
	wavetable[1] = NULL;
	wavetable[2] = NULL;
	squareEnabled = false;
	cycleTunes();

	lfoWavetable = sine;
	wavetable[0] = sawtooth;
	wavetable[1] = NULL;
	wavetable[2] = NULL;
	squareEnabled = false;
	cycleTunes();

	lfoWavetable = sine;
	wavetable[0] = sine;
	wavetable[1] = sawtooth;
	wavetable[2] = triangle;
	squareEnabled = true;
	cycleTunes();
}
