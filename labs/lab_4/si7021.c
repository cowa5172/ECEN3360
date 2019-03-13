#include "main.h"
#include "si7021.h"
#include "i2c.h"
#include "gpio.h"
#include "emu.h"
#include "letimer.h"

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

char ascii[7];

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

void LPM_Enable(void){
    /* Blocking sleep mode */
    EMU_Block(EM2);

    /* Enabling the SCL and SDA lines to allow I2C communication */
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAnd, I2C_SCL_DEF);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAnd, I2C_SDA_DEF);
    
    /* Resetting the I2C state machines on master and Si7021 */
    I2C0_Reset();
}

void LPM_Disable(void){
    /* Disabling the SCL and SDA lines */
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeDisabled, I2C_SCL_DEF);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeDisabled, I2C_SDA_DEF);
    
    /* Deasserting the sensor enable */
    GPIO_PinOutClear(SENSOR_EN_PORT, SENSOR_EN_PIN);

    /* Unblocking sleep mode */
    EMU_Unblock(EM2);
}

uint8_t SI7021_Read_User_Reg(void){
    I2C0_Start(I2C_WRITE);       // Starts I2C in write mode
    I2C0_Write(READ_REG);        // Specifies location of user read register
    I2C0_Start(I2C_READ);        // Restarts I2C in read mode
    uint8_t data = I2C0_Read();  // Reads receive buffer data into variable
    I2C0_Stop();
    return data;
}

void SI7021_Measure_Temp(void){
	I2C0_Send_Abort();
	I2C0_CMD = I2C_CMD_CLEARPC;

    /* Address temperature read register */
    I2C0_Start(I2C_WRITE);
    I2C0_Write(TEMP_REG);

    /* Read 16 bit temperature data */
    I2C0_Start(I2C_READ);
    uint8_t data = I2C0_Read();
    uint16_t temp_code = data << 8;
    I2C0_Send_ACK();
    data = I2C0_Read();
    temp_code = temp_code | data;

    /* Stop I2C */
    I2C0_Stop();

    /* Convert temperature to Celsius */
    float temp = convert_temp(temp_code);
    temp_to_ASCII(temp);
}

float convert_temp(uint16_t data){
    return (175.72 * data / MAX_COUNT - 46.85);
}

void temp_to_ASCII(float temp){
	int temp_int = temp * 10;
	int working;
	int i = 0;
	int place = 1;
	int zeros = 3;

	if (temp < 0){
		ascii[i++] = '-';
		temp_int = temp_int * (-1);
	}
	else ascii[i++] = '+';

	while ((place * 10) < temp_int){
		place = place * 10;
		zeros--;
	}

	for (int j = zeros; j > 0; j--){
		ascii[i++] = ' ';
	}

	while (temp_int > 0){
		working = temp_int / place;
		working += 0x30;
		ascii[i++] = working;
		if (place == 10) ascii[i++] = '.';
		temp_int = temp_int % place;
		if (place == 10 && temp_int == 0) ascii[i++] = '0';
		place = place / 10;
	}
	ascii[i++] = 'C';
}
