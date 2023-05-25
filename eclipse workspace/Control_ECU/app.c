/*
 * app.c
 *
 *  Created on: May 24, 2023
 *      Author: mohah
 */

#include "MCAL/uart/uart.h"


#include <string.h>
#include "avr/io.h"
#include <util/delay.h>


#define PASSWORD_SIZE 6

void setup(){
	UART_init();
}

void rcvPassword(uint8* str){

	uint8 index = 0;

	while(index < PASSWORD_SIZE){
		str[index] = UART_rcvCharacter();
		if( str[index] == '=')
		{
			str[index] = '\0';
		}
		index++;
	}

}

void main(void){


	setup();

	uint8 password[6];
	uint8 rePassword[6];


	for(;;){
		rcvPassword(password);
		rcvPassword(rePassword);


		if(strcmp(password, rePassword) == 0)
			UART_sendCharacter('t');
		else
			UART_sendCharacter('f');
	}


}

