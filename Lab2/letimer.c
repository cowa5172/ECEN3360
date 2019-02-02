#include "main.h"
#include "letimer.h"
#include "gpio.h"
#include "cmu.h"

/*
 * letimer.c
 *
 *  Created on: 22 Jan 2019
 *      Author: Dylan
 */

/*
* Function Definitions
*/

void LETIMER0_init(void){
	// Set comp0 and comp1
	uint32_t vcomp0, vcomp1;
	LETIMER_Init_TypeDef letimer0_init;

	#ifdef LFXO_MODE
		vcomp0 = LFXO_PRESC * LETIMER_PERIOD;
		vcomp1 = vcomp0 - (LFXO_PRESC * LED_ON_TIME);
	#endif
	#ifdef ULFRCO_MODE
		vcomp0 = 
		vcomp1 = 
	#endif


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