#include "main.h"
#include "em_device.h"
#include "em_chip.h"
#include "bsp.h"
#include "gpio.h"
#include "cmu.h"
#include "emu.h"
#include "leuart.h"
#include "ldma.h"
#include "letimer.h"
#include "i2c.h"
#include "si7021.h"
#include "cryotimer.h"
#include "capsense.h"

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
volatile bool scale;
volatile bool temp_on = true;

int main(void){
    EMU_Block(EM4);
    
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

    /* Initialise peripherals */
    cmu_init();
    gpio_init();
    letimer0_init();
    i2c0_init();
    leuart0_init();
    ldma_init();
    cryotimer_setup();
    CAPSENSE_Init();

    /* Enable peripherals */
    LETIMER_Enable(LETIMER0, true);
    I2C_Enable(I2C0, true);
    LEUART_Enable(LEUART0, leuartEnable);
    CRYOTIMER_Enable(true);

    LDMA_Transfer_RX();

    /* Enables interrupts in the core */
    CORE_ATOMIC_IRQ_ENABLE();

    while (1){
        /*
         * Scheduler for no event; when nothing else is happening the CPU
         * enters sleep at the defined energy mode and is woken when a
         * relevant interrupt is received.
         */
        if (event == 0) EMU_Sleep();

        /*********************************************************************/
        /*
         * Scheduler for the COMP1 event; invoked when the LETIMER reaches
         * the COMP1 value, at which point the temperature is measured.
         */
        if (event & COMP1_MASK){
            event &= ~COMP1_MASK;

            /* Measure temperature using the SI7021 */
            SI7021_Measure_Temp(scale);

            /* Reenabling DMA wakeup for TX (disabled in TXC) */
            LEUART0_TXDMAWU_Enable();
            while(LEUART0 -> SYNCBUSY);

            /* Transfer data once TX array is ready */
            EMU_Block(EM3);
            LDMA_Transfer_TX();
        }

        /*********************************************************************/
        /*
         * Scheduler for SIGF event; invoked when the signal frame '#' has
         * been received.
         */
        if (event & SIGF_MASK){
            event &= ~SIGF_MASK;

            /* Enabling RXBLOCK, stops useless RX data from waking processor */
            LEUART0_RXBLOCK_Enable();
            while(LEUART0 -> SYNCBUSY);

            /* Decoding command, resetting transfer to blank RX array */
            LEUART0_Decode();
            LDMA_Transfer_RX();
        }

        /*********************************************************************/
        /*
         * Scheduler for the TXC event; indicates the end of a DMA transfer
         * from memory to the LEUART0 TX buffer, puts the processor back to
         * sleep at EM3, and disables TX DMA wakeup.
         */
        if (event & TXC_MASK){
            event &= ~TXC_MASK;

            /* Disabling TX DMA transfer */
            EMU_Unblock(EM3);
            LEUART0_TXC_Disable();
            LEUART0_TXDMAWU_Disable();
        }

        /*********************************************************************/
        /*
         * Scheduler for the CRYOTIMER event; invoked when the cryotimer hits
         * its set period, and afterwards measures the capacitive touch sensor
         * to see if the "button" at CH0 has been pressed.
         */
        if (event & CRYO_MASK){
        	event &= ~CRYO_MASK;
        	CAPSENSE_Sense();

        	if (CAPSENSE_getPressed(BUTTON0_CHANNEL)){
			    if (temp_on == true){
			    	LETIMER_Enable(LETIMER0, false);
			    	GPIO_PinOutClear(SENSOR_EN_PORT, SENSOR_EN_PIN);
			    	temp_on = false;
			    } else {
			    	LETIMER_Enable(LETIMER0, true);
			    	temp_on = true;
			    }
        	}
        }
    }
}
