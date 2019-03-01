#include "main.h"
#include "leuart.h"
#include "gpio.h"
#include "em_core.h"
/*
 * leuart.c
 *
 *  Created on: 26 Feb 2019
 *      Author: Dylan
 */

static uint8_t write_count = 0;
static char AT[] = "AT+NAMEdyoh";

void leuart0_init(void){
	LEUART_Init_TypeDef leuart_init;
	leuart_init.enable = false;
	leuart_init.refFreq = 0;
	leuart_init.baudrate = 9600;
	leuart_init.databits = leuartDatabits8;
	leuart_init.parity = leuartNoParity;
	leuart_init.stopbits = leuartStopbits1;

	LEUART_Init(LEUART0, &leuart_init);

	LEUART0_Loopback_Enable();

    LEUART0_ROUTELOC = LEUART_ROUTELOC0_TXLOC_LOC18 | LEUART_ROUTELOC0_RXLOC_LOC18;
    LEUART0_ROUTEPEN = LEUART_ROUTEPEN_TXPEN | LEUART_ROUTEPEN_RXPEN;

	NVIC_EnableIRQ(LEUART0_IRQn);
}

void LEUART0_Write(void){
	if (write_count < 11){
		LEUART_Tx(LEUART0, AT[write_count++]);
	}
}

uint8_t LEUART0_Read(void){
	return LEUART0_RX;
}

void LEUART0_IRQHandler(void){
	CORE_ATOMIC_IRQ_DISABLE();
	unsigned int int_flag = LEUART0_FLAG;
	LEUART0_FLAG_CLR = int_flag;

	if (int_flag & LEUART_IF_TXBL){
		LEUART0_TX_Enable();
		event |= TXBL_MASK;
		LEUART0_TXBL_Disable();
	}
	if (int_flag & LEUART_IF_RXDATAV){
		event |= UART_RXDV_MASK;
		LEUART0_RXDATAV_Disable();
	}

	CORE_ATOMIC_IRQ_ENABLE();
}
