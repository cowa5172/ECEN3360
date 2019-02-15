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
#define SI7021_FREQ   400000 // frequency of i2c transmission in hertz
#define SLAVE_ADDR    0x40   // address of the SI7021 peripheral
#define I2C_WRITE     0      // write signal for the i2c
#define I2C_READ      1      // read signal for the i2c
#define WRITE_REG     0xE6   // address of the user write command register
#define READ_REG      0xE7   // address of the user read command register
#define BIT_RES_12    0x81   // specifies 12 bit resolution for the SI7021
#define BIT_RES_14    0x00   // specifies 14 bit resolution for the SI7021


/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/
void i2c0_init(void);
void reset_i2c(void);
void start_i2c(bool);
void stop_i2c(void);
void wait_ACK(void);
void wait_RXDATAV(void);
void write_i2c(uint8_t);
uint8_t read_i2c(void);
void I2C0_IRQHandler(void);
