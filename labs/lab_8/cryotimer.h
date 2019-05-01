#include "em_cryotimer.h"

/******************************************************************************
 * filename: cryotimer.h                                                      *
 *                                                                            *
 * purpose: Contains function declarations and macros used in cryotimer.c     *
 *                                                                            *
 * date created: 23 April 2019                                                *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/

#define CRYOTIMER_Period_Enable() (CRYOTIMER -> IEN |= CRYOTIMER_IEN_PERIOD)
#define CRYOTIMER_Period_Clear()  (CRYOTIMER -> IFC |= CRYOTIMER_IF_PERIOD)

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: cryotimer_setup
 *
 * description: Initialises the cryotimer to allow it to wake up from EM4, and
 *              sets the period to 1000 cycles
 *
 * arguments: none
 *
 * returns: none
 */

void cryotimer_setup(void);

/*****************************************************************************/

/*
 * function name: CRYOTIMER_IRQHandler
 *
 * description: The handler for the cryotimer interrupt. Triggers whenever the
 * 			    cryotimer finishes 1000 cycles and sets the event in the
 * 			    scheduler.
 *
 * arguments: none
 *
 * returns: none
 */

void CRYOTIMER_IRQHandler(void);
