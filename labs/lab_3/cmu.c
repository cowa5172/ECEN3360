#include "main.h"
#include "cmu.h"
#include "emu.h"
#include "letimer.h"

/******************************************************************************
 * filename: cmu.c                                                            *
 *                                                                            *
 * purpose: Contains functions pertaining to the CMU of the Pearl Gecko and   *
 *          that enable the clocks as well as set their frequencies           *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Keith Graham, Dylan Oh, and Mike Fruge                            *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

/*
 * function name: cmu_init
 *
 * description: Configures the clock tree, selects the clocks to be used, and 
 *              initialises the clocks
 * 
 * arguments: none
 * 
 * returns: none
 */

void cmu_init(void){
	CMU_ClockSelectSet(cmuClock_HFPER, cmuSelect_HFXO);
	CMU_ClockEnable(cmuClock_HFPER, true);

	/* Enable the HFPERCLK for desired peripherals such as ADC */
	CMU_ClockSelectSet(cmuClock_HFPER, cmuSelect_HFXO);
	CMU_ClockEnable(cmuClock_HFPER, true);

	/* Enabling LFRCO to be default */
	CMU_OscillatorEnable(cmuOsc_LFRCO, false, false);	// using LFXO or ULFRCO

	/* Routing LF clock to the LF clock tree */
	if (LETIMER0_EM == EM4) {
		CMU_OscillatorEnable(cmuOsc_ULFRCO, true, true);
		CMU_OscillatorEnable(cmuOsc_LFXO, false, false);		// Disable LFXO
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);	// Use ULFRCO in EM3 for LETIMER0
	}
	else {
		CMU_OscillatorEnable(cmuOsc_ULFRCO, false, false);
		CMU_OscillatorEnable(cmuOsc_LFXO, true, true);		// Disable LFXO
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);	// routing clock to LFA
	}

	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_CORELE, true);

	/* Enabling peripheral clocks */
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_LETIMER0, true);
	CMU_ClockEnable(cmuClock_I2C0, true);
}
