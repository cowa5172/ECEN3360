#include "main.h"
#include "ldma.h"
#include "leuart.h"
#include "em_core.h"

/******************************************************************************
 * filename: ldma.c                                                           *
 *                                                                            *
 * purpose: Contains functions pertaining to the operation of the LDMA so the *
 *          LEUART will operate at an even lower energy level                 *
 *                                                                            *
 * date created: 2 April 2019                                                 *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

LDMA_Descriptor_t  ldma_desc_TX;
LDMA_TransferCfg_t ldma_xfer_TX;
LDMA_Descriptor_t  ldma_desc_RX;
LDMA_TransferCfg_t ldma_xfer_RX;

/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/
void ldma_init(void){
    LDMA_Init_t dma_init = LDMA_INIT_DEFAULT;
    LDMA_Init(&dma_init);

    /* Configuring the transfer characteristics to allow for a DMA transfer
       from memory (source) to the TX buffer of the LEUART (destination) seven 
       times once the TX buffer level is high */
    ldma_desc_TX = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(ascii_TX, &(LEUART0_TX), TX_BUF_SIZE);
    ldma_xfer_TX = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_LEUART0_TXBL);
}

void LDMA_Start_Transfer(void){
    LDMA_StartTransfer(TX_DMA_CHANNEL, &ldma_xfer_TX, &ldma_desc_TX);
}

void LDMA_IRQHandler(void){
    CORE_ATOMIC_IRQ_DISABLE();
    unsigned int int_flag = LDMA_IF;
    LDMA_IFC = int_flag;

    /* Enable the TXC interrupt once a transfer has been completed, allowing
       the next transfer to take place once it's ready to transmit */
    if (int_flag & (1 << TX_DMA_CHANNEL)) LEUART0_TXC_Enable();

    CORE_ATOMIC_IRQ_ENABLE();
}
