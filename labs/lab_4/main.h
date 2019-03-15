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
#define ACK_MASK        0b00000100
#define NACK_MASK       0b00001000
#define I2C_RXDV_MASK   0b00010000
#define TXC_MASK        0b00100000
#define TXBL_MASK       0b01000000

extern volatile uint8_t event;
