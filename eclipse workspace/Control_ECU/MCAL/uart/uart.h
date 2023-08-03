/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../std_types.h"
#include "../../common_macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define U2X_ENABLE 1
#define calcluateBaudRateU2X(baud) ( F_CPU / (8UL * baud) ) - 1

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	BITS_FIVE = 0, BITS_SIX, BITS_SEVEN, BITS_EIGHT, BITS_NINE = 7,
}EN_uart_BitData;

typedef enum{
	PARITY_DISABLE = 0, PARITY_RESERVED, PARITY_ENABLE_EVEN, PARITY_ENABLE_ODD,
}EN_uart_parity;

typedef enum{
	STOP_ONE_BIT = 0, STOP_TWO_BIT,
}EN_uart_stopBit;

typedef enum{
	BAUD_2400 = 2400, BAUD_4800 = 4800, BAUD_9600 = 9600,
}EN_uart_baudRate;

typedef struct{
	EN_uart_BitData bit_data;
	EN_uart_parity parity;
	EN_uart_stopBit stop_bit;
	EN_uart_baudRate baud_rate;
}
ST_uart_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

extern volatile uint8 g_uartRcvData;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_init(ST_uart_ConfigType *configType);
void UART_sendCharacter(uint8 data);
void UART_sendArray(uint8 *str, uint8 str_size);
uint8 UART_rcvCharacter();


#endif /* UART_H_ */
