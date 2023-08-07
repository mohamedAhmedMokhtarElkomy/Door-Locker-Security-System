/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Universal Asynchronous Receiver/Transmitter driver
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 * Github: mohamedAhmedMokhtarElkomy
 *
 *******************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "../../std_types.h"
#include "../../common_macros.h"

/*******************************************************************************
 *                                 Definitions                                 *
 *******************************************************************************/

#define CALCULATE_BAUD_RATE(baud) ( F_CPU / (8UL * baud) ) - 1

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

typedef enum{
	UART_BITS_FIVE = 0, UART_BITS_SIX, UART_BITS_SEVEN, UART_BITS_EIGHT, UART_BITS_NINE = 7,
}EN_uart_BitData;

typedef enum{
	UART_PARITY_DISABLE = 0, UART_PARITY_RESERVED, UART_PARITY_ENABLE_EVEN, UART_PARITY_ENABLE_ODD,
}EN_uart_parity;

typedef enum{
	UART_STOP_ONE_BIT = 0, UART_STOP_TWO_BIT,
}EN_uart_stopBit;

typedef enum{
	BAUD_2400 = 2400, BAUD_4800 = 4800, BAUD_9600 = 9600,
}EN_uart_baudRate;

typedef enum{
    UART_U2X_DISABLE = 0, UART_U2X_ENABLE
}EN_uart_u2x;

typedef enum{
    UART_INT_TX_DISABLE = 0, UART_INT_TX_ENABLE
}EN_uart_int_tx;

typedef enum{
    UART_INT_RX_DISABLE = 0, UART_INT_RX_ENABLE
}EN_uart_int_rx;

typedef struct{
	EN_uart_BitData bit_data;
	EN_uart_parity parity;
	EN_uart_stopBit stop_bit;
	EN_uart_baudRate baud_rate;
    EN_uart_u2x u2x;
    EN_uart_int_tx transmitInterrupt;
    EN_uart_int_rx receiveInterrupt;
}
ST_uart_ConfigType;

/*******************************************************************************
 *                             External Variables                              *
 *******************************************************************************/

extern volatile uint8 g_uart_data;


/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

void UART_init(ST_uart_ConfigType *configType);
void UART_sendCharacter(uint8 data);
void UART_sendArray(uint8 *str, uint8 str_size);
uint8 UART_rcvCharacter();
void UART_int_rx_callBack(void (*callBackFunction)(void));
void UART_int_tx_callBack(void (*callBackFunction)(void));

#endif /* UART_H_ */
