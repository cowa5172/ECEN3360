#include "em_letimer.h"
#include "emu.h"

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
#define     LED_ON_TIME     0.4
#define     LETIMER0_EM     3


/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/
void letimer0_init(void);
void LETIMER0_IRQHandler(void);
