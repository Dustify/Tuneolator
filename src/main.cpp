#include "wavetable.h"

HardwareTimer timer(1);

uint32 tickCount = 0;
bool ledState = false;

// temp note stuff here
double xFreq = notes[62];
uint32 xTicksPerWave = ticks_per_second / xFreq;
uint32 xPhasesPerTick = phases / xTicksPerWave;
uint32 xCurrentTick = 0;
// temp note stuff end


void tick() {
	if (tickCount == ticks_per_second) {
		tickCount = 0;
	}

	if (tickCount == 0) {
		digitalWrite(pin_led, ledState ? HIGH : LOW);
		ledState = !ledState;
	}

	// temp note stuff here
	if(xCurrentTick == phases) {
		xCurrentTick = 0;
	}

	uint32 xPhase = xCurrentTick * xPhasesPerTick;
	uint8 xAmplitude = sine[xPhase];

	GPIOA_BASE->ODR = xAmplitude;

	// for (int i = 0; i < bits; i++) {
	// 	digitalWrite(pins[i], ((xAmplitude >> i) & 0x01) == 0 ? LOW : HIGH);
	// }

	xCurrentTick++;
	// temp note stuff end

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
