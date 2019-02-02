#include "emu.h"

/*
 * emu.c
 *
 *  Created on: 29 Jan 2019
 *      Author: Dylan
 */

int sleep_block_counter[MAX_EM_ELEMENTS];

void blockSleepMode(uint8_t minimumMode){
	CORE_ATOMIC_IRQ_DISABLE();
	sleep_block_counter[minimumMode]++;
	CORE_ATOMIC_IRQ_ENABLE();
}

void unblockSleepMode(uint8_t minimumMode){
	CORE_ATOMIC_IRQ_DISABLE();
	if (sleep_block_counter[minimumMode] > 0){
		sleep_block_counter[minimumMode]--;
	}
	CORE_ATOMIC_IRQ_ENABLE();
}

void enter_sleep(void){
	if (sleep_block_counter[EM0] > 0){
		return;
	} else if (sleep_block_counter[EM1] > 0){
		return;
	} else if (sleep_block_counter[EM2] > 0){
		EMU_EnterEM1();
	} else if (sleep_block_counter[EM3] > 0){
		EMU_EnterEM2(true);
	} else {
		EMU_EnterEM3(true);
	}
}
