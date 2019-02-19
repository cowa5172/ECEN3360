#include "i2c.h"

/******************************************************************************
 * filename: i2c.c                                                            *
 *                                                                            *
 * purpose: Contains functions pertaining to the operation of the LETIMER0    *
 *          peripheral, such as initialisation and interrupt handling         *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

/*
 * function name: i2c0_init
 *
 * description: Initialises I2C0 by setting frequencies of the bus, routing
 *              clock and data pins, and enabling interrupts
 *
 * arguments: none
 *
 * returns: none
 */

void i2c0_init(void){
    /* Initialise I2C0 */
    I2C_Init_TypeDef i2c_init;
    i2c_init.enable  = false;            // Disable enable until after setup complete
    i2c_init.master  = true;             // Set to master mode
    i2c_init.refFreq = 0;                // Use currently configured reference clock
    i2c_init.freq    = SI7021_FREQ;      // Set to SI7021 max frequency
    i2c_init.clhr    = i2cClockHLRFast;  // Set to use 4:4 low/high duty cycle
    I2C_Init(I2C0, &i2c_init);

    /* Route SDA and SCL pins */
    I2C0 -> ROUTELOC0 = I2C_ROUTELOC0_SCLLOC_LOC15 | I2C_ROUTELOC0_SDALOC_LOC15;
    I2C0 -> ROUTEPEN  = I2C_ROUTEPEN_SCLPEN | I2C_ROUTEPEN_SDAPEN;
}

/*****************************************************************************/

/*
 * function name: reset_i2c
 *
 * description: Resets the I2C by aborting all signals if the bus is busy
 *
 * arguments: none
 *
 * returns: none
 */

void reset_i2c(void){
    for (int i=0; i<9; i++){
        GPIO_PinOutClear(I2C_SCL_PORT, I2C_SCL_PIN);
        GPIO_PinOutSet(I2C_SCL_PORT, I2C_SCL_PIN);
    }

    if (I2C0 -> STATE & I2C_STATE_BUSY){
        I2C0 -> CMD = I2C_CMD_ABORT;
    }
}

/*****************************************************************************/

/*
 * function name: start_i2c
 *
 * description: Starts the I2C and sends the write signal to the slave
 *              peripheral
 *
 * arguments:
 * argument     type        description
 * --------     ----        -----------
 * RW           bool        determines whether operation is read or write
 * 
 * returns: none
 */

void start_i2c(bool RW){
    I2C0 -> CMD = I2C_CMD_START;
    I2C0 -> TXDATA = (SLAVE_ADDR << 1) | RW;
    wait_ACK();
}

/*****************************************************************************/

/*
 * function name: stop_i2c
 *
 * description: Sends a NACK to the peripheral to cease communication and stops
 *              the I2C
 *
 * arguments: none
 *
 * returns: none
 */

void stop_i2c(void){
    I2C0 -> CMD = I2C_CMD_NACK;
    I2C0 -> CMD = I2C_CMD_STOP;
}

/*****************************************************************************/

/*
 * function name: wait_ACK
 *
 * description: Waits for an ACK interrupt signal to prevent miscommunication
 *
 * arguments: none
 *
 * returns: none
 */

void wait_ACK(void){
    while(!(I2C0 -> IF & I2C_IF_ACK));
    I2C0 -> IFC = I2C_IFC_ACK;
}

/*****************************************************************************/

/*
 * function name: wait_RXDATAV
 *
 * description: Waits for a valid byte in RXDATA
 *
 * arguments: none
 *
 * returns: none
 */

void wait_RXDATAV(void){
    while(!(I2C0 -> IF & I2C_IF_RXDATAV));
}

/*****************************************************************************/

/*
 * function name: write_i2c
 *
 * description: Loads a byte of data to the TX register to be sent to the
 *              peripheral
 *
 * arguments:
 * argument     type        description
 * --------     ----        -----------
 * data         uint8_t     byte to be sent
 *
 * returns: none
 */

void write_i2c(uint8_t data){
    I2C0 -> TXDATA = data;
    wait_ACK();
}

/*****************************************************************************/

/*
 * function name: read_i2c
 *
 * description: Reads a byte of data from the RX register before sending a
 *              NACK signal to cease communication
 *
 * arguments: none
 *
 * returns:
 * return       type        description
 * --------     ----        -----------
 * buf          uint8_t     byte received from peripheral
 */

uint8_t read_i2c(void){
    uint8_t buf = I2C0 -> RXDATA;
    I2C0 -> CMD = I2C_CMD_NACK;
    return buf;
}

/*****************************************************************************/

/*
 * function name: I2C0_IRQHandler
 *
 * description: The interrupt handler for the I2C0
 *
 * arguments: none
 *
 * returns: none
 */

void I2C0_IRQHandler(void){
    CORE_ATOMIC_IRQ_DISABLE();
    unsigned int int_flag = I2C0 -> IF;
    I2C0 -> IFC = int_flag;
    CORE_ATOMIC_IRQ_ENABLE();
}
