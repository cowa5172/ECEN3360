#include "main.h"
#include "leuart.h"
#include "gpio.h"
#include "em_core.h"
#include <string.h>

/*
 * leuart.c
 *
 *  Created on: 26 Feb 2019
 *      Author: Dylan
 */

volatile uint8_t write_count = 0;
volatile uint8_t read_count = 0;
volatile bool stop_TX = false;
volatile bool stop_RX = false;

void leuart0_init(void){
	LEUART_Init_TypeDef leuart_init;
	leuart_init.enable = false;
	leuart_init.refFreq = 0;
	leuart_init.baudrate = 9600;
	leuart_init.databits = leuartDatabits8;
	leuart_init.parity = leuartNoParity;
	leuart_init.stopbits = leuartStopbits1;

	LEUART_Init(LEUART0, &leuart_init);

    LEUART0_ROUTELOC = LEUART_ROUTELOC0_TXLOC_LOC18 | LEUART_ROUTELOC0_RXLOC_LOC18;
    LEUART0_ROUTEPEN = LEUART_ROUTEPEN_TXPEN | LEUART_ROUTEPEN_RXPEN;

	LEUART0 -> STARTFRAME = '?';
	LEUART0 -> SIGFRAME = '#';
	LEUART0 -> STATUS |= LEUART_STATUS_RXBLOCK;
	LEUART0 -> CTRL |= LEUART_CTRL_SFUBRX;

	NVIC_EnableIRQ(LEUART0_IRQn);
}

void LEUART0_Write(void){
	if (write_count < MAX_CHAR_W){
		LEUART_Tx(LEUART0, ascii_TX[write_count++]);
	} else {
		stop_TX = true;
		write_count = 0;
	}
}

void LEUART0_Read(bool flag){
	if (stop_RX == false){
		ascii_RX[read_count++] = LEUART_Rx(LEUART0);
	} else {
		stop_RX = true;
		read_count = 0;
	}
}

bool LEUART0_Decode(){
	bool scale;
	if (ascii_RX[1] == 'D' || ascii_RX[1] == 'd'){
		if (ascii_RX[2] == 'C' || ascii_RX[2] == 'c'){
			scale = CELSIUS;
		}
		if (ascii_RX[2] == 'F' || ascii_RX[2] == 'f'){
			scale = FAHRENHEIT;
		}
	}
	return scale;
}

void LEUART0_IRQHandler(void){
	CORE_ATOMIC_IRQ_DISABLE();
	unsigned int int_flag = LEUART0_FLAG;
	LEUART0_FLAG_CLR = int_flag;

	if (int_flag & LEUART_IF_TXBL){
		event |= TXBL_MASK;
		LEUART0_TX_Disable();    // Disable TX transmission
	}
	if (int_flag & LEUART_IF_RXDATAV){
		event |= UART_RXDV_MASK;
		LEUART0_RX_Disable();    // Disable RX transmission
	}
	if (int_flag & LEUART_IF_STARTF){
		event |= STARTF_MASK;
	}
	if (int_flag & LEUART_IF_SIGF){
		event |= SIGF_MASK;
	}

	CORE_ATOMIC_IRQ_ENABLE();
}
