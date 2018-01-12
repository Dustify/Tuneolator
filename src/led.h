#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "config.h"

// TODO: make port + pin configurable
// TODO: look into making vars private static
class Led {
public:
static uint16 tickCount;
static bool state;

static bool indicatorState;
static uint16 indicatorTickCount;

static void init() {
	GPIOB->regs->CRH = 0x000030;
	GPIOC->regs->CRH = 0x300000;
}

static void indicate() {
	indicatorTickCount = ticks_per_second * 0.1;
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

uint16 Led::tickCount = 0;
bool Led::state = false;

bool Led::indicatorState;
uint16 Led::indicatorTickCount;

#endif
