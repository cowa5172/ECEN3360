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
#define     LFXO_TICKS      32768u
#define     ULFRCO_TICKS    1000u
#define     MAX_COUNT       65536
#define     LETIMER_PERIOD  4
#define     LED_ON_TIME     0.1
#define     LETIMER0_EM     3
#define     LETIMER0_Interrupt_Clear()  (LETIMER0 -> IFC = LETIMER_IFC_COMP0 | LETIMER_IFC_COMP1;)
#define     LETIMER0_Interrupt_Enable() (LETIMER0 -> IEN |= LETIMER_IEN_COMP0 | LETIMER_IEN_COMP1;)

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/
void letimer0_init(void);
void LETIMER0_IRQHandler(void);
