/*
 * uart.h
 *
 *  Created on: May 10, 2023
 *      Author: mohah
 */

#ifndef UART_H_
#define UART_H_

#include "../../std_types.h"
#include "../../common_macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BAUDRATE 9600

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

extern volatile uint8 g_uartRcvData;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_init();
void UART_sendByte(uint8 data);
void UART_sendString(const char *str);


#endif /* UART_H_ */
