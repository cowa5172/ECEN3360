#include "em_emu.h"
#include "em_core.h"
#include "main.h"

/*
 * emu.h
 *
 *  Created on: 29 Jan 2019
 *      Author: Dylan
 */

#ifndef SRC_EMU_H_
#define SRC_EMU_H_

#ifdef LFXO
#define LETIMER0_EM EM3
#endif

#ifdef ULFRCO
#define LETIMER0_EM EM3
#endif

#define MAX_EM_ELEMENTS 5

enum sleepstate_enum {
	EM0 = 0,
	EM1 = 1,
	EM2 = 2,
	EM3 = 3,
	EM4 = 4
};

void blockSleepMode(uint8_t minimumMode);
void unblockSleepMode(uint8_t minimumMode);
void enter_sleep(void);

#endif /* SRC_EMU_H_ */