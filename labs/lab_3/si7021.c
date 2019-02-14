#include "main.h"
#include "si7021.h"
#include "i2c.h"
#include "gpio.h"
#include "emu.h"

/******************************************************************************
 * filename: si7021.c                                                         *
 *                                                                            *
 * purpose: Contains functions pertaining to the operation of the Si7021,     *
 *          including:                                                        *
 *          - management of energy modes and I2C activity and                 *
 *          - measurement and interpretation of temperature data              *
 *                                                                            *
 * date created: 14 Feb 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

/*
 * function name: enable_LPM
 *
 * description: Enables Low Power Management so that the Pearl Gecko operates
 *              in low energy when I2C communications are not occurring by:
 *              - disabling the SCL and SDA lines,
 *              - deasserting the sensor enable, and 
 *              - unblocking sleep mode
 *
 * arguments: none
 *
 * returns: none
 */

void enable_LPM(void){
    /* Disabling relevant I2C interrupts */
    I2C0 -> IEN &= !(I2C_IEN_ACK | I2C_IEN_RXDATAV);

    /* Disabling the SCL and SDA lines */
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeDisabled, I2C_SCL_DEF);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeDisabled, I2C_SDA_DEF);
    
    /* Deasserting the sensor enable */
    GPIO_PinOutClear(SENSOR_EN_PORT, SENSOR_EN_PIN);

    /* Allowing low energy mode */
    unblockSleepMode();
}

/*****************************************************************************/

/*
 * function name: disable_LPM
 *
 * description: Disables Low Power Management so that the I2C can function by
 *              - blocking the energy mode to a minimum of EM1, 
 *              - enabling the SCL and SDA lines to Wired And, and
 *              - resetting the I2C state machines.
 *
 * arguments: none
 *
 * returns: none
 */

void disable_LPM(void){
    /* Preventing I2C from falling below EM1 */
    blockSleepMode(EM2);

    /* Enabling the SCL and SDA lines to allow I2C communication */
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAnd, I2C_SCL_DEF);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAnd, I2C_SDA_DEF);
    
    /* Resetting the I2C state machines on master and Si7021 */
    reset_i2c();

    /* Enabling I2C interrupts */
    I2C0 -> IFC = I2C0_IFC_ACK;
    I2C0 -> IEN |= I2C0_IEN_ACK | I2C0_IEN_RXDATAV;
}

/*****************************************************************************/

/*
 * function name: read_user_reg
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

uint8_t read_user_reg(void){
    start_i2c(I2C_WRITE);       // Starts I2C in write mode
    write_i2c(READ_REG);        // Specifies location of user read register
    start_i2c(I2C_READ);        // Restarts I2C in read mode
    wait_RXDATAV(void);         // Waits for valid data in receive buffer
    uint8_t data = read_i2c();  // Reads receive buffer data into variable
    stop_i2c();                 // Stops I2C
    return data;
}

/*****************************************************************************/

/*
 * function name: measure_temp
 *
 * description: Protocol to measure temperature from the Si7021
 *
 * arguments: none
 *
 * returns:
 * return       type        description
 * --------     ----        -----------
 * data         uint8_t     temperature code from Si7021
 */

uint8_t measure_temp(void){

    return data;
}

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
 * data         uint8_t     temperature code from Si7021
 * 
 * returns: Temperature in celsius
 */

uint8_t convert_temp(uint8_t data){
    return (175.72 * data / 65536 - 46.85);
}