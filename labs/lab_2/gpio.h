#include "main.h"
#include "em_gpio.h"

/******************************************************************************
 * filename: gpio.h                                                           *
 *                                                                            *
 * purpose: contains function declarations and macros used in gpio.c          *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/

/* LED0 properties */
#define	LED0_port       gpioPortF
#define LED0_pin        4
#define LED0_default    false 	  // LED0 off by default

/* LED1 properties */
#define LED1_port       gpioPortF
#define LED1_pin        5
#define LED1_default    false	  // LED1 off by default


/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/
void gpio_init(void);