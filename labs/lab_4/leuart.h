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

extern volatile bool stop_TX;

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/
#define MAX_CHAR           (strlen(ascii))

#define LEUART0_CMD        LEUART0 -> CMD
#define LEUART0_CTRL       LEUART0 -> CTRL
#define LEUART0_INT_EN     LEUART0 -> IEN
#define LEUART0_FLAG       LEUART0 -> IF
#define LEUART0_FLAG_CLR   LEUART0 -> IFC
#define LEUART0_TX         LEUART0 -> TXDATA
#define LEUART0_ROUTELOC   LEUART0 -> ROUTELOC0
#define LEUART0_ROUTEPEN   LEUART0 -> ROUTEPEN

/* LEUART0 Operation Aliases */
#define LEUART0_Loopback_Enable() (LEUART0_CTRL |= LEUART_CTRL_LOOPBK)
#define LEUART0_TX_Enable()       (LEUART0_CMD |= LEUART_CMD_TXEN)
#define LEUART0_TX_Disable()      (LEUART0_CMD |= LEUART_CMD_TXDIS)
#define LEUART0_TXBL_Enable()     (LEUART0_INT_EN |= LEUART_IEN_TXBL)
#define LEUART0_TXBL_Disable()    (LEUART0_INT_EN &= ~LEUART_IEN_TXBL)

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
 * function name: LETIMER0_Write
 *
 * description: Function for sending a byte of data to a UART peripheral.
 *              Written expressly to send the temperature in ASCII format to
 *              the HL-10 bluetooth module.
 *
 * arguments: none
 *
 * returns: none
 */

void LEUART0_Write(void);

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
