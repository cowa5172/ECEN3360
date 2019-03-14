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
#define COMP0_MASK      0b000000001
#define COMP1_MASK      0b000000010
#define ACK_MASK        0b000000100
#define NACK_MASK       0b000001000
#define I2C_RXDV_MASK   0b000010000
#define TXBL_MASK       0b000100000
#define UART_RXDV_MASK  0b001000000
#define STARTF_MASK     0b010000000
#define SIGF_MASK       0b100000000

#define CELSIUS         0
#define FAHRENHEIT      1

extern volatile uint16_t event;
