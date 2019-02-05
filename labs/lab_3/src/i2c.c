#include "i2c.h"

void i2c0_init(void){
	I2C_Init_TypeDef i2c_init;
    
    i2c_init.enable  = false,            /* Enable when initialization done. */
    i2c_init.master  = true,             /* Set to master mode. */
    i2c_init.refFreq = 0,                /* Use currently configured reference clock. */
    i2c_init.freq    = SI7021_FREQ,      /* Set to standard rate assuring being */
    i2c_init.clhr    = i2cClockHLRFast   /* Set to use 4:4 low/high duty cycle. */

    I2C_Init(I2C0, &i2c_init)
}
