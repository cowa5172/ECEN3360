#include "gpio.h"

/******************************************************************************
 * FUNCTION DEFINITIONS 					 								  *
 *****************************************************************************/
void gpio_init(void){
// Set LED ports to be standard output drive with default off (cleared)
//	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_DriveStrengthSet(LED0_PORT, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED0_PORT, LED0_PIN, gpioModePushPull, LED0_DEFAULT);

//	GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_DriveStrengthSet(LED1_PORT, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED1_PORT, LED1_PIN, gpioModePushPull, LED1_DEFAULT);

//	Assert SENSOR_ENABLE
	GPIO_DriveStrengthSet(SENSOR_ENABLE_PORT, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(SENSOR_ENABLE_PORT, SENSOR_ENABLE_PIN, gpioModePushPull, SENSOR_DEFAULT);

//	Initialize SCL and SDA pins
	GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAnd, I2C_SCL_DEFAULT);
	GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAnd, I2C_SDA_DEFAULT);
}
