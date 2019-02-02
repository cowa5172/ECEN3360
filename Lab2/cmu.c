#include "cmu.h"

/******************************************************************************
 * filename: cmu.c															  *
 * 																			  *
 * purpose: Contains functions pertaining to the CMU of the Pearl Gecko and   *
 * 			that enable the clocks as well as set their frequencies           *
 * 																			  *
 * date created: 22 Jan 2019												  *
 *																			  *
 * authors: Dylan Oh and Mike Fruge											  *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS 					 								  *
 *****************************************************************************/

/*
 * function name: cmu_init
 *
 * description: Configures the clock tree, selects the clocks to be used, and 
 * 				initialises the clocks
 * 
 * arguments: none
 * 
 * returns: none
 */

void cmu_init(void){
	CMU_ClockSelectSet(cmuClock_HFPER, cmuSelect_HFXO);
	CMU_ClockEnable(cmuClock_HFPER, true);

	CMU_OscillatorEnable(cmuOsc_LFRCO, false, false);	// using LFXO or ULFRCO

	/* Routing LF clock to the LF clock tree */
	CMU_OscillatorEnable(cmuOsc_ULFRCO, false, false);
	CMU_OscillatorEnable(cmuOsc_LFXO, true, true);		// enable LFXO
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);	// route clock to LFA

	CMU_ClockEnable(cmuClock_LFA, true);
	CMU_ClockEnable(cmuClock_CORELE, true);

	/* Enabline peripheral clocks */
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_LETIMER0, true);
}
