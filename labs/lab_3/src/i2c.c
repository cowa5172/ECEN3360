#include "i2c.h"

void i2c0_init(void){
	I2C_Init_TypeDef i2c_init;
    
    i2c_init.enable  = false;            /* Enable when initialization done. */
    i2c_init.master  = true;             /* Set to master mode. */
    i2c_init.refFreq = 0;                /* Use currently configured reference clock. */
    i2c_init.freq    = SI7021_FREQ;      /* Set to standard rate assuring being */
    i2c_init.clhr    = i2cClockHLRFast;  /* Set to use 4:4 low/high duty cycle. */

    I2C0 -> ROUTELOC0 = I2C_ROUTELOC0_SCLLOC_LOC15 | I2C_ROUTELOC0_SDALOC_LOC15;
    I2C0 -> ROUTEPEN  = I2C_ROUTEPEN_SCLPEN | I2C_ROUTEPEN_SDAPEN;

    I2C_Init(I2C0, &i2c_init);
}

void start_i2c(void){
	I2C0 -> CMD = I2C_CMD_START;
}

void stop_i2c(void){
	I2C0 -> CMD = I2C_CMD_STOP;
}

void wait_i2c(void){
	while(!(I2C0 -> IF & I2C_IF_ACK));
	I2C0 -> IFC = I2C_IFC_ACK;
}

void write_i2c(uint8_t data){
    I2C0 -> TXDATA = data;
    wait_i2c();
}

uint8_t read_i2c(void){
	write_i2c((SLAVE_ADDR << 1) | 1);
	uint8_t buf = I2C0 -> RXDATA;
	I2C0 -> CMD = I2C_CMD_NACK;
	return buf;
}

uint8_t temp_meas(void){
	uint8_t temp;
	start_i2c();
	write_i2c((SLAVE_ADDR << 1) | 0);
	write_i2c(TEMP_READ_REG);
	start_i2c();
	temp = read_i2c();
	stop_i2c();
}
