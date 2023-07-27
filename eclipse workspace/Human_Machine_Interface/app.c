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

	DDRB |= ( 1 << 7);
}

void readAndSendPassword();

void main(void){

	uint8 response = 'w';
	setup();

	LCD_displayString("System loading...");
	LCD_moveCursor(1,0);

	_delay_ms(1000); /* delay 1 sec to be sure that both ECU MCU is running */

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

	while(1){
		LCD_clearScreen();
		LCD_displayString("+ : open door");
		LCD_moveCursor(1,0);
		LCD_displayString("- : change pass");

		uint8 key = KEYPAD_getPressedKey();
		_delay_ms(250);/* it needs at least 200ms to work properly*/
		LCD_clearScreen();

		if( key == '+' ){

			response = 'f';

			while(response == 'f'){
				UART_sendCharacter('+');
				LCD_displayString("plz enter pass: ");
				LCD_moveCursor(1,0);
				readAndSendPassword();
				LCD_clearScreen();

				response = UART_rcvCharacter();
				if(response == 't'){
					//TODO move the motor
					LCD_displayString("Motor is moving");
					response = UART_rcvCharacter();
					LCD_clearScreen();
					break;
				}

				else if(response == 'b'){
					LCD_displayString("Alert");
					PORTB |= ( 1 << 7 );//TODO turn on LED
					//delay 30 sec
					_delay_ms(3000);
					PORTB &= ~( 1 << 7 );//TODO turn of LED
					break;
				}
			}

		}else if( key == '-' ){
			response = 'f';
			while(response == 'f'){
				UART_sendCharacter('-');
				LCD_displayString("plz enter pass: ");
				LCD_moveCursor(1,0);
				readAndSendPassword();
				response = UART_rcvCharacter();

				LCD_clearScreen();
				LCD_displayString("correct");
				_delay_ms(1000);
				LCD_clearScreen();
				if(response == 't'){
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
				}
				else if(response == 'b'){
					LCD_displayString("Alert");
					PORTB |= ( 1 << 7 );//TODO turn on LED
					//delay 30 sec
					_delay_ms(3000);
					PORTB &= ~( 1 << 7 );//TODO turn of LED
					break;
				}
				LCD_clearScreen();
			}
		}
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
