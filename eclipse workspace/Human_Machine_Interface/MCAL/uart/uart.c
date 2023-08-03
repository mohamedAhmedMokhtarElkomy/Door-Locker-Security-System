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
volatile uint8 g_uartRcvData = 'z';


/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
ISR(USART_RXC_vect){
	g_uartRcvData = UDR;
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void UART_init(ST_uart_ConfigType *configType){

	uint16 ubrr_value = 0;

	//	SET_BIT(UCSRB, RXCIE);		/* RX Complete Interrupt Enable */

	SET_BIT(UCSRA, U2X);		/* : Double the USART Transmission Speed */
	SET_BIT(UCSRB, TXEN);		/* Transmitter Enable*/
	SET_BIT(UCSRB, RXEN);		/* Receiver Enable */

	CLEAR_BIT(UCSRC, UMSEL);	/* USART Mode Select 0 -> async, 1 -> sync*/

	UCSRC |= ( configType->bit_data << UCSZ0 ); /* configure number of bits to be send, UCSZ1:0: 11 -> 8-bit */ /* will not work with 9-bits because UCSZ2 not in UCSRC */
	UCSRC |= ( configType->parity << UPM0 );	/* configure parity bits */
	UCSRC |= ( configType->stop_bit << USBS );

#if(U2X_ENABLE == 1)
	ubrr_value = (uint16) calcluateBaudRateU2X(configType->baud_rate);
#else
	ubrr_value = (uint16) calcluateBaudRateU2X(configType->baud_rate * 2);
#endif
//	ubrr_value = (uint16)(( F_CPU / ( BAUDRATE * 8UL )) - 1 );


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

uint8 UART_rcvCharacter(){
	while( BIT_IS_CLEAR(UCSRA, RXC) ){}
	return UDR;
}

