#include "em_emu.h"
#include "emu.h"

/*
 * emu.c
 *
 *  Created on: 29 Jan 2019
 *      Author: Dylan
 */


void blockSleepMode(sleepstate_enum minimumMode){
	CORE_ATOMIC_IRQ_DISABLE();
	sleep_block_counter[minimumMode]++;
	CORE_ATOMIC_IRQ_ENABLE();
}

void unblockSleepMode(sleepstate_enum minimumMode){
	CORE_ATOMIC_IRQ_DISABLE();
	if (sleep_block_counter[minimumMode] > 0){
		sleep_block_counter[minimumMode]--;
	}
	CORE_ATOMIC_IRQ_ENABLE();
}

void sleep(void){
	if (sleep_block_counter[0] > 0){
		return;
	} else if (sleep_block_counter[1] > 0){
		return;
	} else if (sleep_block_counter[2] > 0){
		EMU_EnterEM1();
	} else if (sleep_block_counter[3] > 0){
		EMU_EnterEM2(true);
	} else {
		EMU_EnterEM3();
	}
}
