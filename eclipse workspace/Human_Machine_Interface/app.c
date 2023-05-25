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
void main(void){

	setup();
	UART_rcvCharacter();


	do{

		LCD_displayString("plz enter pass: ");
		LCD_moveCursor(1,0);

		readAndSendPassword();


		LCD_clearScreen();
		LCD_displayString("plz re-enter the");
		LCD_moveCursor(1,0);
		LCD_displayString("same pass:");

		readAndSendPassword();

		uint8 result = UART_rcvCharacter();
		/***************************************************/
		LCD_clearScreen();
		LCD_displayString("Different");
		LCD_moveCursor(1,0);
		LCD_displayString("passwords");


		_delay_ms(3000);
		LCD_clearScreen();

	}while(1);

	LCD_clearScreen();
	LCD_displayString("all is good");
	_delay_ms(3000);

//	for(;;){
//		key = KEYPAD_getPressedKey();
//		LCD_displayCharacter(key);
//		_delay_ms(500); /* it needs at least 200ms to work properly*/
//		UART_sendByte(key);
//	}

}

