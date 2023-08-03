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
#include "HAL/eeprom/eeprom.h"

#include <string.h>
#include "avr/io.h"
#include <util/delay.h>

#define F_CPU 8000000UL

#define ROTATE_MOTOR '+';
#define CREATE_PASS '-';
#define CHECK_PASS 'p';


#define PASSWORD_SIZE 6

static uint8 attempts = 2;

ST_dcMotor_configType dcMotor = { PORTB_ID, PORTB_ID, PIN4_ID, PIN5_ID };
ST_uart_ConfigType uart_configType = {BITS_EIGHT, PARITY_DISABLE, STOP_ONE_BIT, BAUD_9600};

void setup(){
	UART_init(&uart_configType);
	Buzzer_init();
	DcMotor_init(&dcMotor);
	TWI_init();

}

void rcvPassword(uint8* str);
void changePass();
uint8 checkPass();

void main(void){

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
				UART_sendCharacter(' ');

				DcMotor_stop(&dcMotor);
				_delay_ms(3000);
				UART_sendCharacter(' ');

				DcMotor_rotate(&dcMotor, EN_DC_A_CW, 100);
				_delay_ms(15000);
				UART_sendCharacter(' ');

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


	if(strcmp(password, rePassword) == 0){
		for(int i = 0; i < 6; i++){
			EEPROM_writeByte(0x0311+i, password[i]); /* Write 0x0F in the external EEPROM */
			_delay_ms(10);
		}
		UART_sendCharacter('t');
	}
	else
		UART_sendCharacter('f');
}
uint8 checkPass(){
	uint8 default_pass[6] = {'=', '=', '=', '=', '=', '='};
	uint8 password[6] = {'='};
	rcvPassword(password);

	for(int i = 0; i < 6; i++){
		EEPROM_readByte(0x0311+i, &default_pass[i]);
		_delay_ms(10);
	}



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
