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

void letimer0_init(void){
	unsigned int	seconds_ticks, on_ticks;
	unsigned int	letimer0_tick_seconds;
	unsigned int	pres_cal, effective_pres_cal;

	LETIMER_Init_TypeDef letimer0_values;

	if (Letimer0_EM == EM4) letimer0_tick_seconds = ULFRCO_FREQ;
	else letimer0_tick_seconds = LFXO_FREQ;

	// second ticks required before prescaling
	seconds_ticks = Letimer0_Period * letimer0_tick_seconds - 1;	// minus 1 due to count starts from 0 and not 1

	pres_cal = 0;
	effective_pres_cal = 1;
	while ((seconds_ticks / MAX_COUNT) > 0){
		pres_cal++;
		letimer0_tick_seconds = letimer0_tick_seconds >> 1;
		seconds_ticks = Letimer0_Period * letimer0_tick_seconds - 1;	// minus 1 due to count starts from 0 and not 1
		effective_pres_cal = effective_pres_cal << 1;
	}

	on_ticks = seconds_ticks - (Letimer0_On_Time * letimer0_tick_seconds) / 1000;  //Adjust for milli-seconds

	if (effective_pres_cal > 1) CMU_ClockPrescSet(cmuClock_LETIMER0, effective_pres_cal);

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

void LETIMER0_IRQHandler(void){
	/* Grabbing flag source and clearing flags */
	unsigned int int_flag;

	CORE_ATOMIC_IRQ_DISABLE();
	int_flag = LETIMER0 -> IF;
	LETIMER0 -> IFC = int_flag;

	/* LED0 set when counter = COMP0, cleared when counter = COMP1 */
	if (int_flag & LETIMER_IF_COMP0){ GPIO_PinOutSet(LED0_port, LED0_pin); }
	if (int_flag & LETIMER_IF_COMP1){ GPIO_PinOutClear(LED0_port, LED0_pin); }
	CORE_ATOMIC_IRQ_ENABLE();
}
