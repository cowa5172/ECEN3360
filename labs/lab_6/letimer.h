#include "em_letimer.h"

/******************************************************************************
 * filename: letimer.h                                                        *
 *                                                                            *
 * purpose: Contains function declarations and macros used in letimer.c       *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/
#define LFXO_TICKS      32768u
#define ULFRCO_TICKS    1000u
#define MAX_COUNT       65536
#define LETIMER_PERIOD  3
#define LED_ON_TIME     0.025
#define LETIMER0_EM     3

#define LETIMER0_IF     LETIMER0 -> IF
#define LETIMER0_IFC    LETIMER0 -> IFC
#define LETIMER0_IEN    LETIMER0 -> IEN

#define LETIMER_Interrupt_Clear()  (LETIMER0_IFC = LETIMER_IFC_COMP0 | LETIMER_IFC_COMP1)
#define LETIMER_Interrupt_Enable() (LETIMER0_IEN |= LETIMER_IEN_COMP0 | LETIMER_IEN_COMP1)
#define LETIMER0_COMP0_Enable()    (LETIMER0_IEN |= LETIMER_IEN_COMP0)
#define LETIMER0_COMP0_Disable()   (LETIMER0_IEN &= ~LETIMER_IEN_COMP0)
#define LETIMER0_COMP1_Enable()    (LETIMER0_IEN |= LETIMER_IEN_COMP1)
#define LETIMER0_COMP1_Disable()   (LETIMER0_IEN &= ~LETIMER_IEN_COMP1)

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: letimer0_init
 *
 * description: Initialises the LETIMER0 by setting the COMP0 and COMP1
 *              registers, adjusting the prescaler, enabling repeat free mode,
 *              disabling underflow, and enabling interrupts
 *
 * arguments: none
 *
 * returns: none
 */

void letimer0_init(void);

/*****************************************************************************/

/*
 * function name: LETIMER0_IRQHandler
 *
 * description: The interrupt handler for the LETIMER0. When COMP0 is reached,
 *              the handler is called to enable the sensor and prep for I2C
 *              communication to the SI7021. When COMP1 is reached, the handler
 *              is called to exit low energy, perform temperature measurements,
 *              and return to sleep.
 *
 * arguments: none
 *
 * returns: none
 */

void LETIMER0_IRQHandler(void);
