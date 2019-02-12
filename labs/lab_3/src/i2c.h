//***********************************************************************************
// Include files
//***********************************************************************************
#include "main.h"
#include "em_i2c.h"
#include "em_core.h"
#include "gpio.h"

//***********************************************************************************
// defined files
//***********************************************************************************
#define SI7021_FREQ   400000 // Hertz
#define SLAVE_ADDR    0x40
#define I2C_WRITE     0
#define I2C_READ      1
#define READ_REG      0xE7
#define WRITE_REG     0xE6
#define BIT_RES       0x81

// I2C interrupt is IRQ 17

//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
void i2c0_init(void);
void reset_i2c(void);
void start_i2c(bool RW);
void stop_i2c(void);
void wait_i2c(void);
void write_i2c(uint8_t data);
uint8_t read_i2c(void);
uint8_t temp_meas(void);
