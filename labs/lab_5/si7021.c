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

char ascii_TX[7];
char ascii_RX[4];

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

void SI7021_Measure_Temp(bool scale){
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
	float temp = (175.72 * data / MAX_COUNT - 46.85);
	if (scale == FAHRENHEIT) temp = temp * 9 / 5 + 32;
    return temp;
}

void temp_to_ASCII(float temp){
	int temp_int = temp * 10;
	int zero_flag = 0;
	int i = 0;
	int place = 1;
	int zeros = 3;

	/* Determining the sign of the number */
	if (temp < 0){
		ascii_TX[i++] = '-';
		temp_int = temp_int * (-1);
	} else ascii_TX[i++] = '+';

	/* Determining the number of zeros and digits */
	while ((place * 10) <= temp_int){
		place = place * 10;
		zeros--;
	}

	/* Special case where number is less than 1 */
	if (zeros == 3){
		zero_flag = true;
		zeros = 2;
	}

	/* Inserting leading spaces */
	for (int j = zeros; j > 0; j--){
		ascii_TX[i++] = ' ';
	}

	/* Continuation of special case */
	if (zero_flag){
		ascii_TX[i++] = '0';
		ascii_TX[i++] = '.';
	}

	/* Inserting number into string */
	while (place > 0){
		ascii_TX[i++] = (temp_int / place) + 0x30;
		if (place == 10) ascii_TX[i++] = '.';
		temp_int = temp_int % place;
		if (ascii_TX[i - 1] == '.'){
			if (temp_int == 0) ascii_TX[i++] = '0';
			else {
				ascii_TX[i++] = (temp_int / (place / 10)) + 0x30;
			}
			place = 0;
		} else place = place / 10;
	}

	/* Adding Celsius symbol */
	if (scale == CELSIUS) ascii_TX[i++] = 'C';
	if (scale == FAHRENHEIT) ascii_TX[i++] = 'F';
}
