#include "gpio.h"

/******************************************************************************
 * filename: gpio.c                                                           *
 *                                                                            *
 * purpose: Contains functions pertaining to the initialisation of the GPIO   *
 *          of the Pearl Gecko                                                *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Keith Graham, Dylan Oh, and Mike Fruge                            *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
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

void gpio_init(void){
    /* Set LED ports to be standard output drive with default off (cleared) */
	GPIO_DriveStrengthSet(LED0_PORT, gpioDriveStrengthWeakAlternateWeak);
	GPIO_DriveStrengthSet(LED1_PORT, gpioDriveStrengthWeakAlternateWeak);	
	GPIO_PinModeSet(LED0_PORT, LED0_PIN, gpioModePushPull, LED0_DEFAULT);
	GPIO_PinModeSet(LED1_PORT, LED1_PIN, gpioModePushPull, LED1_DEFAULT);

	/* Assert SENSOR_ENABLE */
	GPIO_DriveStrengthSet(SENSOR_EN_PORT, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(SENSOR_EN_PORT, SENSOR_EN_PIN, gpioModePushPull, SENSOR_DEFAULT);

	/* Initialize SCL and SDA pins */
	GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAnd, I2C_SCL_DEFAULT);
	GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAnd, I2C_SDA_DEFAULT);
}
