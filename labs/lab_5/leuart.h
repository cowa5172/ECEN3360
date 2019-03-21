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

extern volatile uint8_t write_count;
extern volatile uint8_t read_count;
extern volatile bool stop_RX;
extern volatile bool stop_TX;

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/

#define MAX_CHAR_W         (strlen(ascii_TX))
#define MAX_CHAR_R         (strlen(ascii_RX))

#define LEUART0_CMD        LEUART0 -> CMD
#define LEUART0_CTRL       LEUART0 -> CTRL
#define LEUART0_STAT       LUEART0 -> STATUS
#define LEUART0_INT_EN     LEUART0 -> IEN
#define LEUART0_FLAG       LEUART0 -> IF
#define LEUART0_FLAG_CLR   LEUART0 -> IFC
#define LEUART0_RX         LEUART0 -> RXDATA
#define LEUART0_TX         LEUART0 -> TXDATA
#define LEUART0_ROUTELOC   LEUART0 -> ROUTELOC0
#define LEUART0_ROUTEPEN   LEUART0 -> ROUTEPEN
#define LEUART0_STARTF     LEUART0 -> STARTFRAME
#define LEUART0_SIGF        LEUART0 -> SIGFRAME

/* LEUART0 Operation Aliases */
#define LEUART0_Loopback_Enable() (LEUART0_CTRL |= LEUART_CTRL_LOOPBK)
#define LEUART0_TX_Enable()       (LEUART0_CMD |= LEUART_CMD_TXEN)
#define LEUART0_TX_Disable()      (LEUART0_CMD |= LEUART_CMD_TXDIS)
#define LEUART0_RX_Enable()       (LEUART0_CMD |= LEUART_CMD_RXEN)
#define LEUART0_RX_Disable()      (LEUART0_CMD |= LEUART_CMD_RXDIS)
#define LEUART0_TXBL_Enable()     (LEUART0_INT_EN |= LEUART_IEN_TXBL)
#define LEUART0_TXBL_Disable()    (LEUART0_INT_EN &= ~LEUART_IEN_TXBL)
#define LEUART0_RXDATAV_Enable()  (LEUART0_INT_EN |= LEUART_IEN_RXDATAV)
#define LEUART0_RXDATAV_Disable() (LEUART0_INT_EN &= ~LEUART_IEN_RXDATAV)

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
