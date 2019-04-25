#include "main.h"
#include "cryotimer.h"
#include "em_core.h"

/******************************************************************************
 * filename: cryotimer.c                                                      *
 *                                                                            *
 * purpose:
 *                                                                            *
 * date created: 23 April 2019                                                *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

void cryotimer_setup(void){
	CRYOTIMER_Init_TypeDef cryo_init;

	cryo_init.enable    = false;
	cryo_init.debugRun  = false;
	cryo_init.em4Wakeup = true;
	cryo_init.osc       = cryotimerOscULFRCO;
	cryo_init.period    = cryotimerPeriod_1k;
	cryo_init.presc     = cryotimerPresc_1;

	CRYOTIMER_Init(&cryo_init);

	CRYOTIMER -> IEN |= CRYOTIMER_IEN_PERIOD;
	NVIC_EnableIRQ(CRYOTIMER_IRQn);
}

void CRYOTIMER_IRQHandler(void){
	CORE_ATOMIC_IRQ_DISABLE();
	event |= CRYO_MASK;
	CRYOTIMER -> IFC |= CRYOTIMER_IF_PERIOD;
	CORE_ATOMIC_IRQ_ENABLE();
}
