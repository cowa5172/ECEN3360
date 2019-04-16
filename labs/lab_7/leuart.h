#include "em_leuart.h"
#include "si7021.h"
#include <string.h>

/******************************************************************************
 * filename: leuart.h                                                         *
 *                                                                            *
 * purpose: Contains function declarations and macros used in leuart.c        *
 *                                                                            *
 * date created: 26 Feb 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/

#define LEUART0_CMD        LEUART0 -> CMD
#define LEUART0_CTRL       LEUART0 -> CTRL
#define LEUART0_STAT       LUEART0 -> STATUS
#define LEUART0_IEN        LEUART0 -> IEN
#define LEUART0_IF         LEUART0 -> IF
#define LEUART0_IFC        LEUART0 -> IFC
#define LEUART0_RX         LEUART0 -> RXDATA
#define LEUART0_TX         LEUART0 -> TXDATA
#define LEUART0_ROUTELOC   LEUART0 -> ROUTELOC0
#define LEUART0_ROUTEPEN   LEUART0 -> ROUTEPEN
#define LEUART0_STARTF     LEUART0 -> STARTFRAME
#define LEUART0_SIGF       LEUART0 -> SIGFRAME

/* LEUART0 Operation Aliases */
#define LEUART0_TXC_Enable()      (LEUART0_IEN |= LEUART_IEN_TXC)
#define LEUART0_TXC_Disable()     (LEUART0_IEN &= ~LEUART_IEN_TXC)
#define LEUART0_TXDMAWU_Enable()  (LEUART0_CTRL |= LEUART_CTRL_TXDMAWU)
#define LEUART0_TXDMAWU_Disable() (LEUART0_CTRL &= ~LEUART_CTRL_TXDMAWU)
#define LEUART0_RXDMAWU_Enable()  (LEUART0_CTRL |= LEUART_CTRL_RXDMAWU)
#define LEUART0_RXDMAWU_Disable() (LEUART0_CTRL &= ~LEUART_CTRL_RXDMAWU)
#define LEUART0_RXBLOCK_Enable()  (LEUART0_CMD |= LEUART_CMD_RXBLOCKEN)
#define LEUART0_STARTF_Enable()   (LEUART0_IEN |= LEUART_IEN_STARTF)
#define LEUART0_SIGF_Enable()     (LEUART0_IEN |= LEUART_IEN_SIGF)
#define LEUART0_SFUBRX_Enable()   (LEUART0_CTRL |= LEUART_CTRL_SFUBRX)

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: leuart0_init
 *
 * description: Initialises the LEUART by specifying the parity, number of data
 *              and stop bits, and baud rate as well as routing pins for TX and
 *              RX communication.
 *
 * arguments: none
 *
 * returns: none
 */

void leuart0_init(void);

/*****************************************************************************/

/*
 * function name: LETIMER0_Read
 *
 * description: Function for reading a byte of data from a UART peripheral.
 *              Written expressly to receive commands from the HL-10 bluetooth
 *              module.
 *
 * arguments: none
 *
 * returns: none
 */

void LEUART0_Read(void);

/*****************************************************************************/

/*
 * function name: LEUART0_Decode
 *
 * description: Function for decoding commands received via bluetooth.
 *
 * arguments: none
 *
 * returns: none
 */

void LEUART0_Decode(void);

/*****************************************************************************/

/*
 * function name: LEUART0_IRQHandler
 *
 * description: The interrupt handler for the LEUART0. Schedules an event when
 *              the TXBL interrupt is set (data is ready to be sent)
 *
 * arguments: none
 *
 * returns: none
 */

void LEUART0_IRQHandler(void);
