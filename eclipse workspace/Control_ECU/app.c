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

#define ROTATE_MOTOR '+';
#define CREATE_PASS '-';
#define CHECK_PASS 'p';


#define PASSWORD_SIZE 6

static uint8 attempts = 3;

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

void changePass(){

	uint8 password[6];
	uint8 rePassword[6];
	rcvPassword(password);
	rcvPassword(rePassword);


	if(strcmp(password, rePassword) == 0)
		UART_sendCharacter('t');
	else
		UART_sendCharacter('f');
}

void checkPass(){
	uint8 default_pass[6] = {'1', '2', '3', '4', '5', '\0'};
	uint8 password[6];
	rcvPassword(password);

	if(strcmp(password, default_pass) == 0)
		UART_sendCharacter('t');
	else{
		if(attempts == 0){
			UART_sendCharacter('b');
			attempts = 3;
		}
		else{
			UART_sendCharacter('f');
			attempts--;
		}
	}
}

void main(void){

	uint8 response = 0;

	setup();

	do{
		response = UART_rcvCharacter();

		if(response == '+' ){
			checkPass();
		}	//TODO move motor
		else if(response == '-')
			checkPass();
		else if(response == 'p')
			changePass();
	}while(1);


}

