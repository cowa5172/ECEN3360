#include "main.h"
#include "em_letimer.h"
#include "cmu.h"
#include "gpio.h"

/******************************************************************************
 * filename: letimer.h														  *
 * 																			  *
 * purpose: contains function declarations and macros used in letimer.c       *
 * 																			  *
 * date created: 22 Jan 2019												  *
 *																			  *
 * authors: Dylan Oh and Mike Fruge											  *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS     					 								  *
 *****************************************************************************/
#define     LFXO_FREQ       32768u
#define     ULFRCO_FREQ     1000u
#define     MAX_COUNT       65535


/******************************************************************************
 * FUNCTION DECLARATIONS 					 								  *
 *****************************************************************************/
void LETIMER0_init(void);
void LETIMER0_IRQHandler(void);

