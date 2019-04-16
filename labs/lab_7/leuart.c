#include "main.h"
#include "leuart.h"
#include "gpio.h"
#include "em_core.h"
#include <string.h>

/******************************************************************************
 * filename: leuart.c                                                         *
 *                                                                            *
 * purpose: Contains functions pertaining to the operation of the LEUART0     *
 *          peripheral, such as initialisation and interrupt handling.        *
 *                                                                            *
 * date created: 26 Feb 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

void leuart0_init(void){
    LEUART_Init_TypeDef  leuart_init;
    leuart_init.enable   = false;
    leuart_init.refFreq  = 0;
    leuart_init.baudrate = 9600;
    leuart_init.databits = leuartDatabits8;
    leuart_init.parity   = leuartNoParity;
    leuart_init.stopbits = leuartStopbits1;

    LEUART_Init(LEUART0, &leuart_init);

    LEUART0_ROUTELOC = LEUART_ROUTELOC0_TXLOC_LOC18 | LEUART_ROUTELOC0_RXLOC_LOC18;
    LEUART0_ROUTEPEN = LEUART_ROUTEPEN_TXPEN | LEUART_ROUTEPEN_RXPEN;

    LEUART0_STARTF = '?';
    LEUART0_SIGF   = '#';
    LEUART0_RXBLOCK_Enable();
    LEUART0_SFUBRX_Enable();
    while(LEUART0 -> SYNCBUSY);

    LEUART0_SIGF_Enable();

    LEUART0_TXDMAWU_Enable();
    LEUART0_RXDMAWU_Enable();
    while(LEUART0 -> SYNCBUSY);

    NVIC_EnableIRQ(LEUART0_IRQn);
}

void LEUART0_Decode(void){
    if (ascii_RX[1] == 'D' || ascii_RX[1] == 'd'){
        if (ascii_RX[2] == 'C' || ascii_RX[2] == 'c') scale = CELSIUS;
        if (ascii_RX[2] == 'F' || ascii_RX[2] == 'f') scale = FAHRENHEIT;
    }
}

void LEUART0_IRQHandler(void){
    CORE_ATOMIC_IRQ_DISABLE();
    unsigned int int_flag = LEUART0_IF;
    LEUART0_IFC = int_flag;

    if (int_flag & LEUART_IF_TXC){
    	event |= TXC_MASK;
    	LEUART0_TXC_Disable();
    }
    if (int_flag & LEUART_IF_SIGF)   event |= SIGF_MASK;

    CORE_ATOMIC_IRQ_ENABLE();
}
