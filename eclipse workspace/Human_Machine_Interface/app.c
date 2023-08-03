/*
 * app.c
 *
 *  Created on: May 24, 2023
 *      Author: mohah
 */

#define F_CPU 8000000UL

#include "HAL/keypad/keypad.h"
#include "HAL/lcd/lcd.h"
#include "MCAL/uart/uart.h"
#include "MCAL/timer/timer.h"

#include <util/delay.h>
#include "avr/io.h"
#include <string.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define F_CPU 8000000UL
#define PASSWORD_SIZE 6


ST_timer1_configType timer1_configType = {TIMER1_MAX_VALUE - TIMER1_ONE_SECOND_CLK_256_8M, TIMER1_MAX_VALUE, TIMER1_CLK_256, TIMER1_NORMAL};

uint16 seconds = 0;

void handleTimer_callBack(){
	if(seconds > 0)
		seconds--;

}

void setup(){
	//	KEYPAD_init();

	LCD_init();
	UART_init();
	Timer1_init(&timer1_configType);
	Timer1_setCallBack(&handleTimer_callBack);
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

void readAndSendPassword();
void changePass();
uint8 checkPass(uint8 key);

void main(void){

	setup();

	LCD_displayString("System loading...");
	LCD_moveCursor(1,0);

	_delay_ms(1000); /* delay 1 second to be sure that both ECU MCU is running */

	LCD_clearScreen();

	changePass();

	while(1){
		LCD_clearScreen();
		LCD_displayString("+ : open door");
		LCD_moveCursor(1,0);
		LCD_displayString("- : change pass");

		uint8 key = KEYPAD_getPressedKey();
		_delay_ms(250);/* it needs at least 200ms to work properly*/
		LCD_clearScreen();

		if( key == '+' ){
			if( checkPass('+') == 1){
				//TODO run motor
				LCD_displayString("Unlocking Door");
				//TODO delay here
				UART_rcvCharacter();
				LCD_clearScreen();
				LCD_displayString("Hold Door");
				UART_rcvCharacter();
				LCD_clearScreen();
				LCD_displayString("Locking Door");
				UART_rcvCharacter();
				LCD_clearScreen();
			}
		}
		else if( key == '-' ){
			if( checkPass('-') == 1){
				LCD_displayString("correct");
				_delay_ms(1000);
				LCD_clearScreen();
				changePass();

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

void changePass(){


	uint8 response = 'w';

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

uint8 checkPass(uint8 key){

	uint8 response = 'w';

	do{
		UART_sendCharacter(key);
		LCD_displayString("plz enter pass: ");
		LCD_moveCursor(1,0);
		readAndSendPassword();
		response = UART_rcvCharacter();
		LCD_clearScreen();

		if(response == 'b'){
			LCD_displayString("ERROR");
			seconds = 60;/* wait here for 60 seconds */
			while(seconds > 0){
				LCD_clearScreen();
				LCD_displayString("ERROR");
				LCD_moveCursor(1,0);
				LCD_integerToString(seconds);
				_delay_ms(250);

			}
			break;
		}
		else if(response == 't'){
			return 1;
		}
	}while(response == 'f');

	return 0;
}


