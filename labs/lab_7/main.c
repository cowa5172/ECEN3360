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

    LDMA_Start_Transfer_RX();

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
            LPM_Enable();
            SI7021_Measure_Temp(scale);
            LPM_Disable();

            /* Enable TX transmission once full ascii string created */
            LEUART0_TXDMAWU_Enable();
            while(LEUART0 -> SYNCBUSY);
            EMU_Block(EM3);
            LDMA_Start_Transfer_TX();
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
            LEUART0_RXBLOCK_Enable();
            while(LEUART0 -> SYNCBUSY);
            LEUART0_Decode();
            LDMA_Start_Transfer_RX();
        }

        /*********************************************************************/
        /*
         * Scheduler for the TXC event; indicates the end of a DMA transfer
         * from memory to the LEUART0 TX buffer, puts the processor back to
         * sleep at EM3, and disables TX DMA wakeup.
         */
        if (event & TXC_MASK){
        	event &= ~TXC_MASK;
        	EMU_Unblock(EM3);
            LEUART0_TXC_Disable();
            LEUART0_TXDMAWU_Disable();
        }
    }
}
