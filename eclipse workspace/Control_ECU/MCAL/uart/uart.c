/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Universal Asynchronous Receiver/Transmitter driver
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 * Github: mohamedAhmedMokhtarElkomy
 *
 *******************************************************************************/

#include "uart.h"
#include "avr/io.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                                 Definitions                                 *
 *******************************************************************************/


/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

volatile uint8 g_uart_data;

/*******************************************************************************
 *                              Private Variables                              *
 *******************************************************************************/

void (*transmitionCallBackFunction)(void);
void (*receiveCallBackFunction)(void);


/*******************************************************************************
 *                              ISR's Definitions                              *
 *******************************************************************************/
ISR(USART_RXC_vect){
	g_uart_data = UDR;
    (*receiveCallBackFunction)();
}

ISR(USART_TXC_vect){
	(*transmitionCallBackFunction)();
}

 /*******************************************************************************
 *                            Functions Definitions                            *
 *******************************************************************************/
void UART_init(ST_uart_ConfigType *configType){

    uint16 ubrr_value = 0;

	UCSRA |= ( configType->u2x << U2X); 					/* Enable Double the USART Transmission Speed */

	UCSRB |= ( 1 << TXEN );									/* Transmitter Enable*/
	UCSRB |= ( 1 << RXEN );									/* Receiver Enable */
	UCSRB |= ( configType-> receiveInterrupt << RXCIE);		/* RX Complete Interrupt Enable */
	UCSRB |= ( configType-> transmitInterrupt << TXCIE);	/* TX Complete Interrupt Enable */

	UCSRC |= ( configType->bit_data << UCSZ0 ); 			/* configure number of bits to be send, UCSZ1:0: 11 -> 8-bit */ /* will not work with 9-bits because UCSZ2 not in UCSRC */
	UCSRC |= ( configType->parity << UPM0 );				/* configure parity bits */
	UCSRC |= ( configType->stop_bit << USBS );				/* configure stop bits */



	if(configType->u2x == UART_U2X_ENABLE)
		ubrr_value = (uint16) CALCULATE_BAUD_RATE(configType->baud_rate);
	else
		ubrr_value = (uint16) CALCULATE_BAUD_RATE(configType->baud_rate * 2);

//	UBRRH = (ubrr_value >> 8) & (0x0F);
	UBRRH = (uint8)(ubrr_value >> 8);
	UBRRL = (uint8) ubrr_value;

}

void UART_sendCharacter(uint8 data){
	while( BIT_IS_CLEAR(UCSRA, UDRE) ){} /* wait if previous byte still sending */
	UDR = data;
}

void UART_sendArray(uint8 *str, uint8 str_size){

	for(int i = 0; i < str_size; i++){
		while( BIT_IS_CLEAR(UCSRA, UDRE) ){} /* wait if previous byte still sending */
		UDR = str[i];
	}

}

uint8 UART_rcvCharacter(){
	while( BIT_IS_CLEAR(UCSRA, RXC) ){}
	return UDR;
}

void UART_int_rx_callBack(void (*callBackFunction)(void)){
	receiveCallBackFunction = callBackFunction;
}

void UART_int_tx_callBack(void (*callBackFunction)(void)){
    transmitionCallBackFunction = callBackFunction;
}
