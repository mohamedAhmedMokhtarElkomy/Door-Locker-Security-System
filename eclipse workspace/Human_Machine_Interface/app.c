/*
 * app.c
 *
 *  Created on: May 24, 2023
 *      Author: mohah
 */

#include "HAL/keypad/keypad.h"
#include "HAL/lcd/lcd.h"
#include "MCAL/uart/uart.h"

#include <util/delay.h>
#include "avr/io.h"
#include <string.h>


#define PASSWORD_SIZE 6

//#define F_CPU 8000000UL

void setup(){
	LCD_init();
//	KEYPAD_init();
	UART_init();
}

void readAndSendPassword();

void main(void){

	uint8 response = 'w';
	setup();

	LCD_displayString("System loading...");
	LCD_moveCursor(1,0);

	_delay_ms(1000); /* delay 1 sec to be sure that both ECU MCU is running */

restart:
	LCD_clearScreen();

	do{
		UART_sendCharacter('p');
		LCD_displayString("plz enter pass: ");
		LCD_moveCursor(1,0);
		readAndSendPassword();
		LCD_clearScreen();

		LCD_displayString("plz re-enter the");
		LCD_moveCursor(1,0);
		LCD_displayString("same pass:");
		readAndSendPassword();
		LCD_clearScreen();

		LCD_displayString("checking password");
		response = UART_rcvCharacter();
		LCD_clearScreen();



		if(response == 't')
		{

			LCD_displayString("Password Saved");
			LCD_moveCursor(1,0);
			LCD_displayString("Successfully");
		}
		else if(response == 'f'){

			LCD_displayString("Different");
			LCD_moveCursor(1,0);
			LCD_displayString("passwords");
		}

		_delay_ms(2000);
		LCD_clearScreen();

	}while(response == 'f');


screen:

	LCD_clearScreen();
	LCD_displayString("+ : open door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : change pass");

	uint8 key = KEYPAD_getPressedKey();
	_delay_ms(250);/* it needs at least 200ms to work properly*/
	LCD_clearScreen();

	if( key == '+' ){
		for(int i = 1; i <= 3; i++){
			UART_sendCharacter('+');
			LCD_displayString("plz enter pass: ");
			LCD_moveCursor(1,0);
			readAndSendPassword();
			LCD_clearScreen();

			response = UART_rcvCharacter();
			if(response == 't'){
				LCD_displayString("Motor is moving");
				response = UART_rcvCharacter();
				LCD_clearScreen();
				break;
			}
		}

		if(response == 'f')
			goto screen;
	}else if( key == '-' ){
		for(int i = 1; i <=3; i++){
			UART_sendCharacter('-');
			LCD_displayString("-)plz enter pass: ");
			LCD_moveCursor(1,0);
			readAndSendPassword();
			response = UART_rcvCharacter();
			if(response == 't')
				break;
			LCD_clearScreen();
		}
		if(response == 'f')
			goto screen;
		goto restart;
	}
}


void readAndSendPassword(){

	uint8 password[PASSWORD_SIZE] = {'=', '=', '=', '=', '=', '='};			/* password that store 5 chars and \0 */
	uint8 password_index = 0;

	for(;;){
		password[password_index] = KEYPAD_getPressedKey();
		_delay_ms(250);/* it needs at least 200ms to work properly*/

		if(password[password_index] == '=' ){ /* if user pressed Enter */
			password[password_index] = '\0';
			break;
		}
		else if(password_index <= 4){ /* index 4 indicates that 5 numbers have been entered*/
			LCD_displayCharacter('*');
			password_index++;
		}
	}

	UART_sendArray(password, PASSWORD_SIZE); /*TODO UART should not used in app layer*/

}
