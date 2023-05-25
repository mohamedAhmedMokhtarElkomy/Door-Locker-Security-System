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
void UART_sendCharacter(uint8 data);
void UART_sendArray(uint8 *str, uint8 str_size);


#endif /* UART_H_ */
