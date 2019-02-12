#include <stdint.h>
#include <stdbool.h>

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
 * MACRO DEFINITIONS     					 								  *
 *****************************************************************************/
#define     LETIMER_PERIOD      1.75
#define     LED_ON_TIME         0.4
#define     LETIMER0_EM         EM3

/* note that LETIMER0_EM is one energy level lower than the one that the Pearl
 * Gecko will operate in; i.e. if LETIMER0_EM is defined as EM3, then the Pearl
 * Gecko will operate in energy mode 2
 */
