/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/
#include "uart.h"

#include "avr/io.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
volatile uint8 g_uartRcvData = 0xFF;


/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
ISR(USART_RXC_vect){
	g_uartRcvData = UDR;
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void UART_init(){

	uint16 ubrr_value = 0;

	SET_BIT(UCSRA, U2X);		/* : Double the USART Transmission Speed */

	SET_BIT(UCSRB, RXCIE);		/* RX Complete Interrupt Enable */
	SET_BIT(UCSRB, TXEN);		/* Transmitter Enable*/
	SET_BIT(UCSRB, RXEN);		/* Receiver Enable */

	CLEAR_BIT(UCSRC, UMSEL);	/* USART Mode Select 0 -> async, 1 -> sync*/
	SET_BIT(UCSRC, UCSZ1);		/* UCSZ1:0: Character Size */
	SET_BIT(UCSRC, UCSZ0);		/* UCSZ1:0: 11 -> 8-bit */


	ubrr_value = (uint16)(( F_CPU / ( BAUDRATE * 8UL )) - 1 );

	UBRRH = (ubrr_value >> 8) & (0x0F);
	UBRRL = ubrr_value;
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
