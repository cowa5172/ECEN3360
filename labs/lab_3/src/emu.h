#include "em_emu.h"
#include "em_core.h"
#include "main.h"

/******************************************************************************
 * filename: emu.h															  *
 * 																			  *
 * purpose: contains function declarations and macros used in emu.c	          *
 * 																			  *
 * date created: 22 Jan 2019												  *
 *																			  *
 * authors: Dylan Oh and Mike Fruge											  *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS     					 								  *
 *****************************************************************************/
enum sleepstate_enum {
	EM0 = 0,
	EM1 = 1,
	EM2 = 2,
	EM3 = 3,
	EM4 = 4
};


/******************************************************************************
 * FUNCTION DECLARATIONS 					 								  *
 *****************************************************************************/
void blockSleepMode(uint8_t minimumMode);
void unblockSleepMode(uint8_t minimumMode);
void enter_sleep(void);