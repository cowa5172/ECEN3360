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
bool reset_flag = false;

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

    /* Initialise LDMA */
    ldma_init();

    /* Enable LETIMER0 */
    LETIMER_Enable(LETIMER0, true);

    /* Enable I2C0 */
    I2C_Enable(I2C0, true);

    /* Enable LEUART0 */
    LEUART_Enable(LEUART0, leuartEnable);

    while(LEUART0 -> SYNCBUSY);

    /* Enables interrupts in the core */
    CORE_ATOMIC_IRQ_ENABLE();

    while (1) {
        /*
         * Scheduler for no event; when nothing else is happening the CPU
         * enters sleep at the defined energy mode and is awoken when a
         * relevant interrupt is received.
         */
        if (event == 0) EMU_Sleep();

        /*********************************************************************/
        /*
         * Scheduler for STARTF event; invoked when the start frame '?' has
         * been received and RXBLOCK has automatically been disabled.
         */
        if (event & STARTF_MASK){
            event &= ~STARTF_MASK;

            /* Check if startframe has been repeated before sigframe received;
               reset_flag is set true the first time a startframe has been
               received and is only disabled once a sigframe is received. In
               the event that a second startframe has been received before a
               sigframe, read_count is reset to overwrite the previous
               aborted command. */
            if (reset_flag == false) reset_flag = true;
            else read_count = 0;
            LEUART0_RXDATAV_Enable();
        }

        /*********************************************************************/
        /*
         * Scheduler for RXDATAV event; only active when RXBLOCK is disabled
         * following a STARTF interrupt and before it is reenabled following a
         * SIGF interrupt.
         */
        if (event & RXDV_MASK){
            event &= ~RXDV_MASK;
            LEUART0_Read();

            /* If full command has been received, disable RXDATAV interrupts.
               Otherwise, keep RXDATAV interrupts enable to receive more data. */
            if (stop_RX) LEUART0_RXDATAV_Disable();
            else LEUART0_RXDATAV_Enable();
        }

        /*********************************************************************/
        /*
         * Scheduler for SIGF event; invoked when the signal frame '#' has
         * been received.
         */
        if (event & SIGF_MASK){
            event &= ~SIGF_MASK;

            /* When sigframe has been received, RX transmission is stopped,
               read_count is reset to 0 to allow for the next RX command, and
               reset_flag is set false to indicate that no startframe has been
               received. Temperature scale is decoded and RX is blocked. */
            reset_flag = false;
            LEUART0_CMD |= LEUART_CMD_RXBLOCKEN;
            LEUART0_RXDATAV_Disable();
            LEUART0_Decode();
            read_count = 0;
        }

        /*********************************************************************/
        /*
         * Scheduler for the COMP0 event; invoked when the LETIMER reaches
         * the COMP0 value, at which point the SI7021 temperature sensor
         * is enabled.
         */
        if (event & COMP0_MASK){
            event &= ~COMP0_MASK;
            GPIO_PinOutSet(SENSOR_EN_PORT, SENSOR_EN_PIN);
        }

        /*********************************************************************/
        /* 
         * Scheduler for the COMP1 event; invoked when the LETIMER reaches
         * the COMP1 value, at which point the temperature is measured.
         */
        if (event & COMP1_MASK){
            event &= ~COMP1_MASK;

            /* Measure temperature using the SI7021 */
            LPM_Enable();
            SI7021_Measure_Temp(scale);
            LPM_Disable();

            /* Enable TX transmission once full ascii string created */
            LEUART0_TXDMAWU_Enable();
            EMU_Block(EM3);
            LDMA_Start_Transfer();
        }

        /*********************************************************************/
        /*
         * Scheduler for the TXC event; invoked when the temperature has been
         * converted into an array of ascii values and stopped once all those
         * values have been transmitted.
         */
        if (event & TXC_MASK){
        	event &= ~TXC_MASK;
        	EMU_Unblock(EM3);
            LEUART0_TXC_Disable();
            LEUART0_TXDMAWU_Disable();
        }
    }
}
