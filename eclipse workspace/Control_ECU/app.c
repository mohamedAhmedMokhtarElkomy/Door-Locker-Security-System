/*
 * app.c
 *
 *  Created on: May 24, 2023
 *      Author: mohah
 */
#define F_CPU 8000000UL

#include "MCAL/uart/uart.h"
#include "MCAL/i2c/i2c.h"
#include "HAL/buzzer/buzzer.h"
#include "HAL/dc_motor/dcMotor.h"

#include <string.h>
#include "avr/io.h"
#include <util/delay.h>

#define F_CPU 8000000UL

#define ROTATE_MOTOR '+';
#define CREATE_PASS '-';
#define CHECK_PASS 'p';


#define PASSWORD_SIZE 6

static uint8 attempts = 2;

DcMotor_configType dcMotor = { PORTB_ID, PORTB_ID, PIN4_ID, PIN5_ID };

void setup(){
	UART_init();
	Buzzer_init();
	DcMotor_init(&dcMotor);
	TWI_init();

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

uint8 checkPass(){
	uint8 default_pass[6] = {'1', '2', '3', '4', '5', '\0'};
	uint8 password[6];
	rcvPassword(password);

	if(strcmp(password, default_pass) == 0){
		UART_sendCharacter('t');
		attempts = 2;
		return 1;
	}
	else{
		if(attempts == 0){
			UART_sendCharacter('b');
			Buzzer_on();
			//TODO delay 1 min
			_delay_ms(5000);
			Buzzer_off();
			UART_sendCharacter('b');
			attempts = 2;
		}
		else{
			UART_sendCharacter('f');
			attempts--;
		}

		return 0;
	}
}

void main(void){

	TWI_start();

	TWI_writeByte(0x10);
	TWI_stop();

	uint8 response = 0;

	setup();

	do{
		response = UART_rcvCharacter();
		uint8 result = 0;

		if(response == '+' ){
			result = checkPass();
			if(result == 1){
				DcMotor_rotate(&dcMotor, EN_DC_CW, 100);
				_delay_ms(15000);
				DcMotor_stop(&dcMotor);
				_delay_ms(3000);
				DcMotor_rotate(&dcMotor, EN_DC_A_CW, 100);
				_delay_ms(15000);
				DcMotor_stop(&dcMotor);

				UART_sendCharacter(' ');

			}
		}
		else if(response == '-')
		{
			result = checkPass();
			if(result == 1)
				changePass();

		}
		else if(response == 'p')
			changePass();
	}while(1);


}
