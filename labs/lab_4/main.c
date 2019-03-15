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

volatile uint8_t event = 0;

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

    while(LEUART0 -> SYNCBUSY);

    /* Enables interrupts in the core */
    CORE_ATOMIC_IRQ_ENABLE();

    while (1) {
        if (event == 0) EMU_Sleep();
        if (event & COMP0_MASK){
            event &= ~COMP0_MASK;
            GPIO_PinOutSet(SENSOR_EN_PORT, SENSOR_EN_PIN);
        }
        if (event & COMP1_MASK){
            event &= ~COMP1_MASK;

            /* Measure temperature */
            LPM_Enable();
            SI7021_Measure_Temp();
            LPM_Disable();

            /* Enable TX to transmit full temp to bluetooth module */
            LEUART_Enable(LEUART0, leuartEnable);
            stop_TX = false;
            LEUART0_TXBL_Enable();
        }
        if (event & TXBL_MASK){
            event &= ~TXBL_MASK;  // Remove event from scheduler
            LEUART0_Write();      // If TX buffer full, write

            /* 
             * Disable TXBL if temperature is done transmitting, else reenable
             * for more transmissions.
             */
            if (stop_TX) LEUART0_TXBL_Disable();
            else LEUART0_TXBL_Enable();
        }
    }
}
