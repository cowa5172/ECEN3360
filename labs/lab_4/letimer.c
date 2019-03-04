#include "main.h"
#include "letimer.h"
#include "gpio.h"
#include "cmu.h"
#include "emu.h"
#include "i2c.h"
#include "si7021.h"

/******************************************************************************
 * filename: letimer.c                                                        *
 *                                                                            *
 * purpose: Contains functions pertaining to the operation of the LETIMER0    *
 *          peripheral, such as initialisation and interrupt handling         *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Keith Graham, Dylan Oh, and Mike Fruge                            *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

void letimer0_init(void){
    unsigned int    period_ticks, on_ticks;
    unsigned int    letimer_freq;
    unsigned int    prescaler, eff_prescaler;
  
    /* Determining the frequency to use based on energy mode */
    if (LETIMER0_EM == EM4) letimer_freq = ULFRCO_TICKS;
    else letimer_freq = LFXO_TICKS;

    /* Calculating the number of ticks in the period of the LETIMER; 
       minus 1 component accounts for 0 start indexing in C */
    period_ticks = LETIMER_PERIOD * letimer_freq - 1;

    /* Calculating and setting the prescaler and adjusting period_ticks */
    prescaler = 0;
    eff_prescaler = 1;
    while ((period_ticks / MAX_COUNT) > 0){
        prescaler++;
        letimer_freq = letimer_freq >> 1;
        period_ticks = LETIMER_PERIOD * letimer_freq - 1;
        eff_prescaler = eff_prescaler << 1;
    }

    /* Calculating the number of ticks the timer signal is "on" */
    on_ticks = period_ticks - (LED_ON_TIME * letimer_freq);

    if (eff_prescaler > 1) CMU_ClockPrescSet(cmuClock_LETIMER0, eff_prescaler);

    /* Initialising LETIMER0 */
    LETIMER_Init_TypeDef letimer_init;
  
    letimer_init.bufTop   = false;
    letimer_init.comp0Top = true;
    letimer_init.debugRun = false;
    letimer_init.enable   = false;                  // disabling during init
    letimer_init.out0Pol  = 0;
    letimer_init.out1Pol  = 0;
    letimer_init.repMode  = letimerRepeatFree;      // setting repeat free mode
    letimer_init.ufoa0    = letimerUFOANone;        // disabling underflow
    letimer_init.ufoa1    = letimerUFOANone;        // disabling underflow

    LETIMER_Init(LETIMER0, &letimer_init);          // Initialising

    /* Setting time compare values */
    LETIMER_CompareSet(LETIMER0, 0, period_ticks);  // setting comp0 register
    LETIMER_CompareSet(LETIMER0, 1, on_ticks);      // setting comp1 register

    /* Initialising interrupts on LETIMER COMP0 and COMP1 */
    LETIMER_Interrupt_Clear();
    LETIMER_Interrupt_Enable();

    EMU_Block(LETIMER0_EM);

    NVIC_EnableIRQ(LETIMER0_IRQn);
}

void LETIMER0_IRQHandler(void){
    unsigned int int_flag;

    /* Disabling other interrupts, grabbing flag source and clearing flags */
    CORE_ATOMIC_IRQ_DISABLE();
    int_flag = LETIMER0_FLAG;
    LETIMER0_FLAG_CLR = int_flag;

    /* Sensor enabled when timer reaches COMP0 */
    if (int_flag & LETIMER_IFC_COMP0){
    	event |= COMP0_MASK;
    	LETIMER0_COMP0_Disable();
    }

    /* Temperature read when timer reaches COMP1 */
    if (int_flag & LETIMER_IFC_COMP1){
    	event |= COMP1_MASK;
        LETIMER0_COMP1_Disable();
    }

    /* Reenabling interrupts */
    CORE_ATOMIC_IRQ_ENABLE();
}
