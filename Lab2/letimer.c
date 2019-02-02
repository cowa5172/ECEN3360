#include "letimer.h"

/*
 * letimer.c
 *
 *  Created on: 22 Jan 2019
 *      Author: Dylan
 */

/******************************************************************************
 * FUNCTION DEFINITIONS 					 								  *
 *****************************************************************************/

/*
 * function name: LETIMER0_init
 *
 * description: Initialises the LETIMER0 by setting the COMP0 and COMP1
 *  			registers, adjusting the prescaler, enabling repeat free mode,
 *
 *
 */

void LETIMER0_init(void){
	// Set comp0 and comp1
	uint32_t vcomp0, vcomp1, eff_freq, prescaler;
	LETIMER_Init_TypeDef letimer0_init;

	vcomp0 = LFXO_FREQ * LETIMER_PERIOD;
	vcomp1 = vcomp0 - (LFXO_FREQ * LED_ON_TIME);
	eff_freq = LFXO_FREQ;
	prescaler = 1;

	// Set prescaler
	while (vcomp0 / MAX_COUNT){
		eff_freq = eff_freq >> 1;
		prescaler = prescaler << 1;
		vcomp0 = eff_freq * LETIMER_PERIOD;
	}

	if (prescaler != 1){
		CMU_ClockPrescSet(cmuClock_LETIMER0, prescaler);
	}

	vcomp1 = vcomp0 - eff_freq * LED_ON_TIME;

	// Initialise LETIMER0
	letimer0_init.bufTop   = false;
	letimer0_init.comp0Top = true;
	letimer0_init.debugRun = false;
	letimer0_init.enable   = false;
	letimer0_init.out0Pol  = 0;
	letimer0_init.out1Pol  = 0;
	letimer0_init.repMode  = letimerRepeatFree;
	letimer0_init.topValue = 0;
	letimer0_init.ufoa0    = letimerUFOANone;
	letimer0_init.ufoa1    = letimerUFOANone;

	LETIMER_Init(LETIMER0, &letimer0_init);

	LETIMER_CompareSet(LETIMER0, 0, vcomp0);
	LETIMER_CompareSet(LETIMER0, 1, vcomp1);

	LETIMER0 -> IFC = LETIMER_IFC_COMP0 | LETIMER_IFC_COMP1;
	LETIMER0 -> IEN |= LETIMER_IEN_COMP0 | LETIMER_IEN_COMP1;

	NVIC_EnableIRQ(LETIMER0_IRQn);
}

/*****************************************************************************/

void LETIMER0_IRQHandler(){
	uint32_t int_flag;
	int_flag = LETIMER_IntGet(LETIMER0);
	LETIMER0 -> IFC = int_flag;

	if (int_flag & LETIMER_IF_COMP0){
		GPIO_PinOutSet(LED0_port, LED0_pin);
	}
	if (int_flag & LETIMER_IF_COMP1){
		GPIO_PinOutClear(LED0_port, LED0_pin);
	}
}
