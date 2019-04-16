#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * filename: main.h                                                           *
 *                                                                            *
 * purpose: contains function declarations and macros used in main.c as well  *
 *          as changeable macros to be used by the instruction team to        *
 *          evaluate the code                                                 *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

extern volatile uint8_t event;
extern volatile bool scale;

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/

#define COMP1_MASK    0b001
#define TXC_MASK      0b010
#define SIGF_MASK     0b100
#define CELSIUS       0
#define FAHRENHEIT    1
