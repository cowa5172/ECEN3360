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
#define	LED0_PORT       gpioPortF
#define LED0_PIN        4
#define LED0_DEF        false      // default state of LED0 (off)

/* LED1 properties */
#define LED1_PORT       gpioPortF
#define LED1_PIN        5
#define LED1_DEF        false      // default state of LED1 (off)

/* SI7021 clock and data properties */
#define I2C_SCL_PORT    gpioPortC
#define I2C_SCL_PIN     11
#define I2C_SCL_DEF     false      // default state of SCL (low)
#define I2C_SDA_PORT    gpioPortC
#define I2C_SDA_PIN     10
#define I2C_SDA_DEF     false      // default state of SDA (low)

/* Sensor properties */
#define SENSOR_EN_PORT  gpioPortB
#define SENSOR_EN_PIN   10
#define SENSOR_EN_DEF	false      // default state of sensor_enable (disabled)


/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: gpio_init
 *
 * description: Initialises all of the GPIO to be used
 * 
 * arguments: none
 * 
 * returns: none
 */

void gpio_init(void);
