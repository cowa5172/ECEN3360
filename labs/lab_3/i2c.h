#include "main.h"
#include "em_i2c.h"
#include "em_core.h"
#include "gpio.h"

/******************************************************************************
 * filename: i2c.h                                                            *
 *                                                                            *
 * purpose: contains function declarations and macros used in i2c.c           *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/
#define SI7021_FREQ     400000 // frequency of i2c transmission in hertz
#define SLAVE_ADDR      0x40   // address of the SI7021 peripheral
#define I2C_WRITE       0      // write signal for the i2c
#define I2C_READ        1      // read signal for the i2c

// Register macro defintions
#define I2C0_CMD        I2C0 -> CMD
#define I2C0_INT_EN     I2C0 -> IEN
#define I2C0_FLAG       I2C0 -> IF
#define I2C0_FLAG_CLR   I2C0 -> IFC
#define I2C0_TXBUF      I2C0 -> TXDATA
#define I2C0_RXBUF      I2C0 -> RXDATA
#define I2C0_ROUTELOC   I2C0 -> ROUTELOC0
#define I2C0_ROUTEPEN   I2C0 -> ROUTEPEN

// Macro function definitions
#define I2C0_Is_Busy()      (I2C0 -> STATE & I2C_STATE_BUSY)
#define I2C0_Send_Start()   (I2C0_CMD = I2C_CMD_START)
#define I2C0_Send_Stop()    (I2C0_CMD = I2C_CMD_STOP)
#define I2C0_Send_Abort()   (I2C0_CMD = I2C_CMD_ABORT)
#define I2C0_Send_ACK()     (I2C0_CMD = I2C_CMD_ACK)
#define I2C0_Send_NACK()    (I2C0_CMD = I2C_CMD_NACK)
#define I2C0_Clear_ACK()    (I2C0_FLAG_CLR = I2C_IFC_ACK)
#define I2C0_Int_Clear()	(I2C0_FLAG_CLR = I2C_IFC_ACK)
#define I2C0_Int_Enable()	(I2C0_INT_EN |= I2C_IEN_ACK | I2C_IEN_RXDATAV)
#define I2C0_Int_Disable()  (I2C0_INT_EN &= !(I2C_IEN_ACK | I2C_IEN_RXDATAV))

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
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

void i2c0_init(void);

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

void I2C0_Reset(void);

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

void I2C0_Start(bool);

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

void I2C0_Stop(void);

void I2C0_Write(uint8_t);

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

uint8_t I2C0_Read(void);

void I2C0_Wait_RXDATAV(void);
void I2C0_Wait_ACK(void);

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

void I2C0_IRQHandler(void);
