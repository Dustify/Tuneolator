#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "config.h"

// TODO: make port + pin configurable
// TODO: look into making vars private static
class Led {
public:
static uint32_t tickCount;
static bool state;

static bool indicatorState;
static uint32_t indicatorTickCountStart;
static uint32_t indicatorTickCount;

static void init() {
	GPIOB->regs->CRH = 0x000030;
	GPIOC->regs->CRH = 0x300000;

	indicatorTickCountStart = ticks_per_second * 0.1;
}

static void indicate() {
	indicatorTickCount = indicatorTickCountStart;
	GPIOB->regs->BSRR = (1<<9);
	indicatorState = true;
}

static void tick() {
	if (tickCount == ticks_per_second) {
		state = !state;

		GPIOC->regs->BSRR = state ? (1<<13) : (1<<29);

		tickCount = 0;
	}

	if (indicatorState) {
		if (indicatorTickCount > 0) {
			indicatorTickCount--;
		}

		if (indicatorTickCount == 0) {
			GPIOB->regs->BSRR = (1<<25);
			indicatorState = false;
		}
	}

	tickCount++;
}
};

uint32_t Led::tickCount = 0;
bool Led::state = false;

bool Led::indicatorState;
uint32_t Led::indicatorTickCountStart;
uint32_t Led::indicatorTickCount;

#endif
