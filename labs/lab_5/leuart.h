#include "em_leuart.h"
#include "si7021.h"
#include <string.h>

/*
 * leuart.h
 *
 *  Created on: 26 Feb 2019
 *      Author: Dylan
 */

#ifndef SRC_LEUART_H_
#define SRC_LEUART_H_

extern volatile bool stop_RX;
extern volatile bool stop_TX;

#define MAX_CHAR_W         (strlen(ascii_TX))
#define MAX_CHAR_R         (strlen(ascii_RX))

#define LEUART0_CMD        LEUART0 -> CMD
#define LEUART0_CTRL       LEUART0 -> CTRL
#define LEUART0_INT_EN     LEUART0 -> IEN
#define LEUART0_FLAG       LEUART0 -> IF
#define LEUART0_FLAG_CLR   LEUART0 -> IFC
#define LEUART0_RX         LEUART0 -> RXDATA
#define LEUART0_TX         LEUART0 -> TXDATA
#define LEUART0_ROUTELOC   LEUART0 -> ROUTELOC0
#define LEUART0_ROUTEPEN   LEUART0 -> ROUTEPEN

#define LEUART0_Loopback_Enable() (LEUART0_CTRL |= LEUART_CTRL_LOOPBK)
#define LEUART0_TX_Disable()      (LEUART0_CMD &= ~LEUART_CMD_TXEN)
#define LEUART0_RX_Disable()      (LEUART0_CMD &= ~LEUART_CMD_RXEN)
#define LEUART0_TXBL_Enable()     (LEUART0_INT_EN |= LEUART_IEN_TXBL)
#define LEUART0_TXBL_Disable()    (LEUART0_INT_EN &= ~LEUART_IEN_TXBL)
#define LEUART0_RXDATAV_Enable()  (LEUART0_INT_EN |= LEUART_IEN_RXDATAV)
#define LEUART0_RXDATAV_Disable() (LEUART0_INT_EN &= ~LEUART_IEN_RXDATAV)

void leuart0_init(void);
void LEUART0_Write(void);
void LEUART0_Read(bool);
void LEUART0_IRQHandler(void);
#endif /* SRC_LEUART_H_ */
