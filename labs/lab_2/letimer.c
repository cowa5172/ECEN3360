#include "letimer.h"

/******************************************************************************
 * filename: letimer.c														  *
 * 																			  *
 * purpose: Contains functions pertaining to the operation of the LETIMER0    *
 * 			peripheral, such as initialisation and interrupt handling         *
 * 																			  *
 * date created: 22 Jan 2019												  *
 *																			  *
 * authors: Dylan Oh and Mike Fruge											  *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS 					 								  *
 *****************************************************************************/

/*
 * function name: LETIMER0_init
 *
 * description: Initialises the LETIMER0 by setting the COMP0 and COMP1
 *  			registers, adjusting the prescaler, enabling repeat free mode,
 *				disabling underflow, and enabling interrupts
 * 
 * arguments: none
 * 
 * returns: none
 */

void LETIMER0_init(void){
	/* Calculating and setting prescaler, comp0, and comp1 */
	uint32_t vcomp0, vcomp1, eff_freq, prescaler;

	vcomp0 = LFXO_FREQ * LETIMER_PERIOD;
	vcomp1 = vcomp0 - (LFXO_FREQ * LED_ON_TIME);
	eff_freq = LFXO_FREQ;
	prescaler = 1;

	while (vcomp0 / MAX_COUNT){
		eff_freq = eff_freq >> 1;				// halving effective freq
		prescaler = prescaler << 1;				// doubling prescaler
		vcomp0 = eff_freq * LETIMER_PERIOD;		// recalculating comp0
	}
	if (prescaler != 1){ CMU_ClockPrescSet(cmuClock_LETIMER0, prescaler); }

	vcomp1 = vcomp0 - eff_freq * LED_ON_TIME;	// recalculating comp1


	/* Initialising LETIMER0 */
	LETIMER_Init_TypeDef letimer0_init;

	letimer0_init.bufTop   = false;
	letimer0_init.comp0Top = true;
	letimer0_init.debugRun = false;
	letimer0_init.enable   = false;				// disabling during init
	letimer0_init.out0Pol  = 0;
	letimer0_init.out1Pol  = 0;
	letimer0_init.repMode  = letimerRepeatFree; // setting repeat free mode
	letimer0_init.topValue = 0;
	letimer0_init.ufoa0    = letimerUFOANone;	// disabling underflow
	letimer0_init.ufoa1    = letimerUFOANone;	// disabling underflow

	LETIMER_Init(LETIMER0, &letimer0_init);		// Initialising

	LETIMER_CompareSet(LETIMER0, 0, vcomp0);	// setting comp0 register
	LETIMER_CompareSet(LETIMER0, 1, vcomp1);	// setting comp1 register


	/* Initialising interrupts on LETIMER COMP0 and COMP1 */
	LETIMER0 -> IFC = LETIMER_IFC_COMP0 | LETIMER_IFC_COMP1;
	LETIMER0 -> IEN |= LETIMER_IEN_COMP0 | LETIMER_IEN_COMP1;

	NVIC_EnableIRQ(LETIMER0_IRQn);				// enabling nested interrupts
}

/*****************************************************************************/

/*
 * function name: LETIMER0_IRQHandler
 *
 * description: The interrupt handler for the LETIMER0. Called when either
 * 				COMP0 or COMP1 is reached in the timer and is used to turn on
 * 				and off LED0 periodically.
 * 
 * arguments: none
 * 
 * returns: none
 */

void LETIMER0_IRQHandler(){
	/* Grabbing flag source and clearing flags */
	uint32_t int_flag;
  
  CORE_ATOMIC_IRQ_DISABLE();
	int_flag = LETIMER_IntGet(LETIMER0);
	LETIMER0 -> IFC = int_flag;

	/* LED0 set when counter = COMP0, cleared when counter = COMP1 */
	if (int_flag & LETIMER_IF_COMP0){ GPIO_PinOutSet(LED0_port, LED0_pin); }
	if (int_flag & LETIMER_IF_COMP1){ GPIO_PinOutClear(LED0_port, LED0_pin); }

  CORE_ATOMIC_IRQ_ENABLE();
}
