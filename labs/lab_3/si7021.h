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
#define WRITE_REG     0xE6   // address of the user write command register
#define READ_REG      0xE7   // address of the user read command register
#define TEMP_REG      0xE3   // address of the measure temp hold master mode
#define BIT_RES_12    0x81   // specifies 12 bit resolution for the SI7021
#define BIT_RES_14    0x00   // specifies 14 bit resolution for the SI7021

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/
uint8_t read_user_reg(void);
uint8_t measure_temp(void);
