#include "em_ldma.h"

/******************************************************************************
 * filename: ldma.h                                                           *
 *                                                                            *
 * purpose: Contains function declarations and macros used in ldma.c          *
 *                                                                            *
 * date created: 2 April 2019                                                 *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/

#define XFER_COUNT     8
#define RX_DMA_CHANNEL 0
#define TX_DMA_CHANNEL 1
#define TX_BUF_SIZE    7
#define RX_BUF_SIZE    20

#define LDMA_IF  (LDMA -> IF)
#define LDMA_IFC (LDMA -> IFC)

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: ldma_init
 *
 * description: Initialises the LDMA by configuring it to default settings and
 *              initialises the transfer characteristics by specifying the 
 *              source and destination addresses as well as the length of the 
 *              transfer and the trigger (TXBL for the TX transfer)
 *
 * arguments: none
 *
 * returns: none
 */

void ldma_init(void);

/*****************************************************************************/

/*
 * function name: LDMA_Transfer_TX
 *
 * description: Begins the transfer from memory to the TX buffer
 *
 * arguments: none
 *
 * returns: none
 */

void LDMA_Transfer_TX(void);

/*****************************************************************************/

/*
 * function name: LDMA_Start_Transfer_RX
 *
 * description: Begins the transfer from the RX buffer to memory
 *
 * arguments: none
 *
 * returns: none
 */

void LDMA_Transfer_RX(void);

/*****************************************************************************/

/*
 * function name: LDMA_IRQHandler
 *
 * description: The interrupt handler for the LDMA, currently configured to
 *              handle an exception generated once a 7-byte transfer is done
 *
 * arguments: none
 *
 * returns: none
 */

void LDMA_IRQHandler(void);
