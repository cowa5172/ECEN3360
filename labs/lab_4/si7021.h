/******************************************************************************
 * filename: si7021.h                                                         *
 *                                                                            *
 * purpose: Contains function declarations and macros used in si7021.c        *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

extern char ascii[7];

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/
#define WRITE_REG      0xE6   // address of the user write command register
#define READ_REG       0xE7   // address of the user read command register
#define TEMP_REG       0xE3   // address of the measure temp hold master mode
#define BIT_RES_12     0x81   // specifies 12 bit resolution for the SI7021
#define BIT_RES_14     0x00   // specifies 14 bit resolution for the SI7021
#define THRESHOLD_TEMP 15

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: LPM_Enable
 *
 * description: Enables Load Power Management so that the I2C can function by
 *              - blocking the energy mode to a minimum of EM1, 
 *              - enabling the SCL and SDA lines to Wired And, and
 *              - resetting the I2C state machines.
 *
 * arguments: none
 *
 * returns: none
 */

void LPM_Enable(void);

/*****************************************************************************/

/*
 * function name: LPM_Disable
 *
 * description: Disables Load Power Management so that the Pearl Gecko operates
 *              in low energy when I2C communications are not occurring by:
 *              - disabling the SCL and SDA lines,
 *              - deasserting the sensor enable, and 
 *              - unblocking sleep mode
 * 
 * arguments: none
 *
 * returns: none
 */

void LPM_Disable(void);

/*****************************************************************************/

/*
 * function name: SI7021_Read_User_Reg
 *
 * description: Protocol to read User Register 1 on the Si7021
 *
 * arguments: none
 *
 * returns:
 * return       type        description
 * --------     ----        -----------
 * data         uint8_t     user register 1 data
 */

uint8_t SI7021_Read_User_Reg(void);

/*****************************************************************************/

/*
 * function name: SI7021_Measure_Temp
 *
 * description: Protocol to measure temperature from the Si7021
 *
 * arguments: none
 *
 * returns:
 * return       type        description
 * --------     ----        -----------
 * data         float       temperature code from Si7021
 */

void SI7021_Measure_Temp(void);

/*****************************************************************************/

/*
 * function name: convert_temp
 *
 * description: Converts temperature code received from the Si7021 into a
 *              Celsius temperature value
 *
 * arguments:
 * argument     type        description
 * --------     ----        -----------
 * data         uint16_t    temperature code from Si7021
 * 
 * returns: Temperature in celsius (float)
 */

float convert_temp(uint16_t);

void temp_to_ASCII(float);
