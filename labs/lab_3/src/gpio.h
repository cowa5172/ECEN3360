#include "main.h"
#include "em_gpio.h"

/******************************************************************************
 * filename: gpio.h 														  *
 * 																			  *
 * purpose: contains function declarations and macros used in gpio.c          *
 * 																			  *
 * date created: 22 Jan 2019												  *
 *																			  *
 * authors: Dylan Oh and Mike Fruge											  *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS 	    				 								  *
 *****************************************************************************/

/* LED0 properties */
#define	LED0_PORT		gpioPortF
#define LED0_PIN        4
#define LED0_DEFAULT	false 	  // LED0 off by default

/* LED1 properties */
#define LED1_PORT       gpioPortF
#define LED1_PIN        5
#define LED1_DEFAULT	false	  // LED1 off by default

/* SI7021 clock and data properties */
#define I2C_SCL_PORT    gpioPortC
#define I2C_SCL_PIN     11
#define I2C_SCL_DEFAULT false

#define I2C_SDA_PORT    gpioPortC
#define I2C_SDA_PIN     10
#define I2C_SDA_DEFAULT false

// location 15 for SCL and SDA
// Enable in gpio


// Route
// Route enable

/******************************************************************************
 * FUNCTION DECLARATIONS  					 								  *
 *****************************************************************************/
void gpio_init(void);