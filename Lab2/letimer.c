#include "letimer.h"
/*
 * letimer.c
 *
 *  Created on: 22 Jan 2019
 *      Author: Dylan
 */

#define LETIMER_PRESC

void LETIMER0_init(void){
	LETIMER_Init_TypeDef* letimer;
	  letimer -> enable = false;         	  /**< Start counting when initialization completes. */
	  letimer -> debugRun = false;       	  /**< Counter shall keep running during debug halt. */
	#if defined(LETIMER_CTRL_RTCC0TEN)
	  letimer -> rtcComp0Enable = false; 	  /**< Start counting on RTC COMP0 match. */
	  letimer -> rtcComp1Enable = false; 	  /**< Start counting on RTC COMP1 match. */
	#endif
	  letimer -> comp0Top = false;       	  /**< Load COMP0 register into CNT when counter underflows. */
	  letimer -> bufTop = false;         	  /**< Load COMP1 into COMP0 when REP0 reaches 0. */
	  letimer -> out0Pol = 0;        		  /**< Idle value for output 0. */
	  letimer -> out1Pol = 0;        		  /**< Idle value for output 1. */
	  letimer -> ufoa0 = letimerUFOANone;     /**< Underflow output 0 action. */
	  letimer -> ufoa1 = letimerUFOANone;     /**< Underflow output 1 action. */
	  letimer -> repMode = letimerRepeatFree; /**< Repeat mode. */
	  letimer -> topValue = 0;       		  /**< Top value. Counter wraps when top value matches counter value is reached. */

	// Set comp0
	// Set comp1
	CMU_ClockPrescSet(cmuClock_LETIMER0, LETIMER_PRESC);// Set prescalar
	// Set to free running mode
	int seconds_ticks = ;
	int on_ticks = ;
	LETIMER_CompareSet(letimer, 0, seconds_ticks);
	LETIMER_CompareSet(letimer, 1, on_ticks);
	LETIMER_Enable(letimer, 1); // Enable LETIMER0
}

void LETIMER_Interrupt_Init(void){
	int_flag = LETIMER0
	LETIMER0 -> IFC = LETIMER_IFC_UF | LETIMER_IFC_COMP1; // Clear LETIMER0 interrupt flags
	LETIMER0 -> IEN = LETIMER_IEN_UF | LETIMER_IEN_COMP1; // Enable COMP0 and COMP1 interrupts
}

void Sleep_Block_Mode(unsigned int EM){

}

void Sleep_UnBlock_Mode(unsigned int EM){

}

void Enter_Sleep(void){

}
