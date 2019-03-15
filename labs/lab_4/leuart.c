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

static uint8_t write_count = 0;
volatile bool stop_TX = false;

void leuart0_init(void){
    LEUART_Init_TypeDef leuart_init;
    leuart_init.enable = false;             // Disabling during init
    leuart_init.refFreq = 0;
    leuart_init.baudrate = 9600;            // Setting baud rate to 9600
    leuart_init.databits = leuartDatabits8; // Specifying 8 data bits per frame
    leuart_init.parity = leuartNoParity;    // Specifying no parity
    leuart_init.stopbits = leuartStopbits1; // Specifying 1 stop bit per frame

    LEUART_Init(LEUART0, &leuart_init);

    /* Routing ports/pins for TX and RX lines */
    LEUART0_ROUTELOC = LEUART_ROUTELOC0_TXLOC_LOC18 | LEUART_ROUTELOC0_RXLOC_LOC18;
    LEUART0_ROUTEPEN = LEUART_ROUTEPEN_TXPEN | LEUART_ROUTEPEN_RXPEN;

    NVIC_EnableIRQ(LEUART0_IRQn);
}

void LEUART0_Write(void){
    if (write_count < MAX_CHAR) LEUART_Tx(LEUART0, ascii[write_count++]);
    else {
        stop_TX = true;
        write_count = 0;
    }
}

void LEUART0_IRQHandler(void){
    CORE_ATOMIC_IRQ_DISABLE();
    unsigned int int_flag = LEUART0_FLAG;
    LEUART0_FLAG_CLR = int_flag;

    /* Scheduling TXBL interrupt */
    if (int_flag & LEUART_IF_TXBL){
        event |= TXBL_MASK;
        LEUART0_TXBL_Disable();
    }

    CORE_ATOMIC_IRQ_ENABLE();
}
