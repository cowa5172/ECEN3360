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

void gpio_init(void){
    /* Set LED ports to be standard output drive with default off (cleared) */
    GPIO_DriveStrengthSet(LED0_PORT, gpioDriveStrengthWeakAlternateWeak);
    GPIO_DriveStrengthSet(LED1_PORT, gpioDriveStrengthWeakAlternateWeak);	
    GPIO_PinModeSet(LED0_PORT, LED0_PIN, gpioModePushPull, LED0_DEF);
    GPIO_PinModeSet(LED1_PORT, LED1_PIN, gpioModePushPull, LED1_DEF);

    /* Deassert SENSOR_ENABLE */
    GPIO_DriveStrengthSet(SENSOR_EN_PORT, gpioDriveStrengthWeakAlternateWeak);
    GPIO_PinModeSet(SENSOR_EN_PORT, SENSOR_EN_PIN, gpioModePushPull, SENSOR_EN_DEF);

    /* Initialise SCL and SDA pins */
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeDisabled, I2C_SCL_DEF);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeDisabled, I2C_SDA_DEF);

    GPIO_DriveStrengthSet(LEUART_TX_PORT, gpioDriveStrengthWeakAlternateWeak);
    GPIO_DriveStrengthSet(LEUART_RX_PORT, gpioDriveStrengthWeakAlternateWeak);
    GPIO_PinModeSet(LEUART_TX_PORT, LEUART_TX_PIN, gpioModePushPull, LEUART_TX_DEF);
    GPIO_PinModeSet(LEUART_RX_PORT, LEUART_RX_PIN, gpioModeInput, LEUART_RX_DEF);
}
