#include "main.h"
#include "si7021.h"
#include "i2c.h"
#include "gpio.h"
#include "emu.h"
#include "letimer.h"

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
    I2C0 
    /* Disabling the SCL and SDA lines */
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeDisabled, I2C_SCL_DEFAULT);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeDisabled, I2C_SDA_DEFAULT);
    
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
    /* Preventing I2C from exceeding EM1 */
    blockSleepMode(EM2);

    /* Enabling the SCL and SDA lines to allow I2C communication */
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAnd, I2C_SCL_DEFAULT);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAnd, I2C_SDA_DEFAULT);
    
    /* Resetting the I2C state machines on master and SI7021 */
    reset_i2c();

    I2C0 -> IFC = I2C0_IFC_ACK;
    I2C0 -> IEN |= I2C0_IEN_ACK | I2C0_IEN_RXDATAV;
}

/*****************************************************************************/

/*
 * function name: read_user_reg
 *
 * description: Protocol to read User Register 1 on the SI7021
 *
 * arguments: none
 *
 * returns:
 * return       type        description
 * --------     ----        -----------
 * data         uint8_t     user register 1 data
 */

uint8_t read_user_reg(void){
    start_i2c(I2C_WRITE);       // Start I2C to initiate a write
    write_i2c(READ_REG);        // Write the location of the user read register
    start_i2c(I2C_READ);        // Restart the I2C to initiate a read
    wait_RXDATAV(void);         // Wait for valid data in receive buffer
    uint8_t data = read_i2c();  // Pull data from buffer into local variable
    stop_i2c();                 // Stop I2C
    return data;
}

/*****************************************************************************/

/*
 * function name: measure_temp
 *
 * description: Protocol to measure temperature from the SI7021
 *
 * arguments: none
 *
 * returns:
 * return       type        description
 * --------     ----        -----------
 * data         uint8_t     temperature code from SI7021
 */

uint8_t measure_temp(void){
    start_i2c(I2C_WRITE);
    write_i2c(TEMP_REG);
    start_i2c(I2C_READ);
    return data;
}

uint8_t convert_temp(uint8_t data){
    return (175.72 * data / MAX_COUNT - 46.85);
}