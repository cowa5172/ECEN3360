#include <stdint.h>
#include <stdbool.h>
#include "em_core.h"

/******************************************************************************
 * filename: main.h				    										  *
 * 																			  *
 * purpose: contains function declarations and macros used in main.c as well  *
 *          as changeable macros to be used by the instruction team to        *
 *          evaluate the code                                                 *
 * 																			  *
 * date created: 22 Jan 2019												  *
 *																			  *
 * authors: Dylan Oh and Mike Fruge											  *
 *****************************************************************************/

/******************************************************************************
 * GLOBAL VARIABLES     					 								  *
 *****************************************************************************/
#define		MAX_EM_ELEMENTS 	5
volatile uint32_t sleep_block_counter[MAX_EM_ELEMENTS];

/******************************************************************************
 * MACRO DEFINITIONS     					 								  *
 *****************************************************************************/
#define     LETIMER_PERIOD      4
#define     LED_ON_TIME         0.5
#define     LETIMER0_EM         EM2

/* note that LETIMER0_EM is one energy level lower than the one that the Pearl
 * Gecko will operate in; i.e. if LETIMER0_EM is defined as EM3, then the Pearl
 * Gecko will operate in energy mode 2
 */