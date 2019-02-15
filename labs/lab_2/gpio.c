#include "main.h"
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

    // Set LED ports to be standard output drive with default off (cleared)
    GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthWeakAlternateWeak);
    GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, LED0_default);

    GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthWeakAlternateWeak);
    GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, LED1_default);

}