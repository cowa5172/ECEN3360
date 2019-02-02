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