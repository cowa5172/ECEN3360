#include "main.h"
#include "em_device.h"
#include "em_chip.h"
#include "bsp.h"
#include "gpio.h"
#include "cmu.h"
#include "letimer.h"
#include "emu.h"
#include "i2c.h"

/******************************************************************************
 * filename: main.c                              							                *
 * 						                                    			                      *
 * purpose: initialises all peripherals and modules before entering sleep     *
 *          in a defined energy mode                                          *
 * 																			                                      *
 * date created: 22 Jan 2019												                          *
 *																			                                      *
 * authors: Keith Graham, Dylan Oh, and Mike Fruge											      *
 *****************************************************************************/

int main(void)
{
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

  /* Enable LETIMER0 */
  LETIMER_Enable(LETIMER0, true);
  I2C_Enable(I2C0, true);

  /* Determines minimum sleep mode */
  blockSleepMode(LETIMER0_EM);

  /* Enables interrupts in the core */
  CORE_ATOMIC_IRQ_ENABLE();

  while (1) {
      enter_sleep();
	    temp_meas();
  }
}
