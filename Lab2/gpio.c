//***********************************************************************************
// Include files
//***********************************************************************************
#include "main.h"
#include "gpio.h"

//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************


//***********************************************************************************
// functions
//***********************************************************************************
void gpio_init(void){

	// Set LED ports to be standard output drive with default off (cleared)
//	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, LED0_default);

//	GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, LED1_default);

}

void LETIMER0_IRQHandler(void){
	int flag = LETIMER_IntGet(LETIMER0);
	if ((flag & LETIMER_IFC_UF) != false){
		GPIO_PinOutClear(LED0_port, LED0_pin);
	} else if ((flag & LETIMER_IFC_COMP1) != false){
		GPIO_PinOutSet(LED0_port, LED0_pin);
	} else {
		GPIO_PinOutSet(LED1_port, LED1_pin);
	}
	LETIMER_IntClear(LETIMER0);
}
