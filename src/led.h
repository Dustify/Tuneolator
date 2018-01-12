#include <Arduino.h>
#include "config.h"

// TODO: make port + pin configurable
// TODO: look into making vars private static
class Led {
public:
static uint16 tickCount;
static bool state;

static void init() {
	GPIOC->regs->CRH = 0x300000;
}

static void tick() {
	if (tickCount == ticks_per_second) {
		state = !state;

		GPIOC->regs->BSRR = state ? (1<<13) : (1<<29);

		tickCount = 0;
	}

	tickCount++;
}
};

uint16 Led::tickCount = 0;
bool Led::state = false;
