#include "i2c.h"

/******************************************************************************
 * filename: i2c.c                                                            *
 *                                                                            *
 * purpose: Contains driver functions for I2C0, including basic operations    *
 *          like start and stop, read and write, initialisation, etc.         *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

void i2c0_init(void){
    I2C_Init_TypeDef i2c_init;
    i2c_init.enable  = false;            // Disable during initialisation
    i2c_init.master  = true;             // Set master mode
    i2c_init.refFreq = 0;                // Use current reference clock
    i2c_init.freq    = SI7021_FREQ;      // Set to SI7021 max frequency
    i2c_init.clhr    = i2cClockHLRFast;  // Set to use 4:4 low/high duty cycle
    I2C_Init(I2C0, &i2c_init);

    /* Route SDA and SCL pins */
    I2C0_ROUTELOC = I2C_ROUTELOC0_SCLLOC_LOC15 | I2C_ROUTELOC0_SDALOC_LOC15;
    I2C0_ROUTEPEN = I2C_ROUTEPEN_SCLPEN | I2C_ROUTEPEN_SDAPEN;

    I2C0_Reset();
}

void I2C0_Reset(void){
    for (int i = 0; i < 9; i++){
        GPIO_PinOutClear(I2C_SCL_PORT, I2C_SCL_PIN);
        GPIO_PinOutSet(I2C_SCL_PORT, I2C_SCL_PIN);
    }
    if (I2C0_Is_Busy()) I2C0_Send_Abort();
}

void I2C0_Start(bool RW){
    I2C0_Send_Start();
    I2C0_TXBUF = (SLAVE_ADDR << 1) | RW;
    I2C0_Wait_ACK();
}

void I2C0_Stop(void){
    I2C0_Send_NACK();
    I2C0_Send_Stop();
}

void I2C0_Write(uint8_t data){
    I2C0_TXBUF = data;
    I2C0_Wait_ACK();
}

uint8_t I2C0_Read(void){
    I2C0_Wait_RXDATAV();
    return I2C0_RXBUF;
}

void I2C0_Wait_RXDATAV(void){
    while(!(I2C0_FLAG & I2C_IF_RXDATAV));
}

void I2C0_Wait_ACK(void){
    while(!(I2C0_FLAG & I2C_IF_ACK));
    I2C0_Clear_ACK();
}
