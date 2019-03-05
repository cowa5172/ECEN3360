#include "main.h"
#include "em_device.h"
#include "em_chip.h"
#include "bsp.h"
#include "gpio.h"
#include "cmu.h"
#include "letimer.h"
#include "emu.h"
#include "i2c.h"
#include "leuart.h"
#include "si7021.h"

/******************************************************************************
 * filename: main.c                                                           *
 *                                                                            *
 * purpose: initialises all peripherals and modules before entering sleep     *
 *          in a defined energy mode                                          *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Keith Graham, Dylan Oh, and Mike Fruge                            *
 *****************************************************************************/

volatile uint32_t event = 0;

int main(void){
    EMU_Block(EM3);
    
    EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
    CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

    /* Chip errata */
    CHIP_Init();

    /* Init DCDC regulator and HFXO with kit specific parameters */
    /* Initialize DCDC. Always start in low-noise mode. */
    EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;
    EMU_DCDCInit(&dcdcInit);
    em23Init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
    EMU_EM23Init(&em23Init);
    CMU_HFXOInit(&hfxoInit);

    /* Switch HFCLK to HFXO and disable HFRCO */
    CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
    CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

    /* Initialise clocks */
    cmu_init();

    /* Initialise GPIO */
    gpio_init();

    /* Initialise LETIMER0 */
    letimer0_init();

    /* Initialise I2C0 */
    i2c0_init();

    /* Initialise LEUART0 */
    leuart0_init();

    /* Enable LETIMER0 */
    LETIMER_Enable(LETIMER0, true);

    /* Enable I2C0 */
    I2C_Enable(I2C0, true);

    /* Enable LEUART0 */
    LEUART_Enable(LEUART0, leuartEnable);

    /* Enables interrupts in the core */
    CORE_ATOMIC_IRQ_ENABLE();

    bool UART_EN = false;

    while(LEUART0 -> SYNCBUSY);
    while (1) {
    	if (UART_EN == false){
    		UART_EN = true;
    		LEUART0_TXBL_Enable();
    		LEUART0_RXDATAV_Enable();
    	}
        if (event == 0){
        	EMU_Sleep();
        }
        if (event & COMP0_MASK){
        	GPIO_PinOutSet(SENSOR_EN_PORT, SENSOR_EN_PIN);
            event &= ~COMP0_MASK;
            LETIMER0_COMP0_Enable();
        }
        if (event & COMP1_MASK){
            LPM_Enable();
            float temp = SI7021_Measure_Temp();
            if (temp < THRESHOLD_TEMP)
            	GPIO_PinOutSet(LED0_PORT, LED0_PIN);
            else
            	GPIO_PinOutClear(LED0_PORT, LED0_PIN);
            LPM_Disable();
            LETIMER0_COMP1_Enable();
            event &= ~COMP1_MASK;
        }
        if (event & ACK_MASK){

			event &= ~ACK_MASK;
        }
        if (event & NACK_MASK){

        	event &= ~NACK_MASK;
        }
        if (event & I2C_RXDV_MASK){

        	event &= ~I2C_RXDV_MASK;
        }
        if (event & TXC_MASK){

        	event &= ~TXC_MASK;
        }
        if (event & TXBL_MASK){
        	event &= ~TXBL_MASK;            // Remove event from scheduler
            LEUART0_Write();                // If TX buffer full, write
            if (stop_TX){
            	LEUART0_TX_Disable();
            } else{
            	LEUART0_TXBL_Enable();      // Enable TX interrupts
            }
        }
        if (event & UART_RXDV_MASK){
        	event &= ~UART_RXDV_MASK;       // Remove event from scheduler
            uint8_t data = LEUART0_Read();  // If RX buffer full, read
            if (stop_RX){
            	LEUART0_RX_Disable();
            } else{
            	LEUART0_RXDATAV_Enable();      // Enable TX interrupts
            }
        }
    }
}
