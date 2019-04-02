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

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/
#define COMP0_MASK      0b00000001
#define COMP1_MASK      0b00000010
#define TXBL_MASK       0b00000100
#define UART_RXDV_MASK  0b00001000
#define STARTF_MASK     0b00010000
#define SIGF_MASK       0b00100000

#define CELSIUS         0
#define FAHRENHEIT      1

extern volatile uint8_t event;
extern volatile bool scale;
