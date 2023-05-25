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

//#define F_CPU 8000000UL

void setup(){
	LCD_init();
//	KEYPAD_init();
	UART_init();
}

void createPassword();

void main(void){



	uint8 password[6];			/* password that store 5 chars and \0 */

	setup();



	do{
		uint8 password_index = 0;

		LCD_displayString("plz enter pass: ");
		LCD_moveCursor(1,0);

		for(;;){
			password[password_index] = KEYPAD_getPressedKey();
			_delay_ms(250);/* it needs at least 200ms to work properly*/

			if(password[password_index] == '=' ){ /* if user pressed Enter */
				password[password_index] = '\0';
				break;
			}
			else if(password_index <= 4){ /* index 4 indicates that 5 numbers have been entered*/
				LCD_displayCharacter(password[password_index]); /*TODO replace it with '*' */
				password_index++;
			}
		}

		LCD_clearScreen();
		LCD_displayString("plz re-enter the");
		LCD_moveCursor(1,0);
		LCD_displayString("same pass:");

		password_index = 0;
		uint8 confirmation_password[6];

		for(;;){

			confirmation_password[password_index] = KEYPAD_getPressedKey();
			_delay_ms(250);/* it needs at least 200ms to work properly*/

			if(confirmation_password[password_index] == '=' ){ /* if user pressed Enter */
				confirmation_password[password_index] = '\0';
				break;
			}
			else if(password_index <= 4){ /* index 4 indicates that 5 numbers have been entered*/
				LCD_displayCharacter(confirmation_password[password_index]); /*TODO replace it with '*' */
				password_index++;
			}
		}

		if(strcmp(password, confirmation_password) == 0){
			break;
		}

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

