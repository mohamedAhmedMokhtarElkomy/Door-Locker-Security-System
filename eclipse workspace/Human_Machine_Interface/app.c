/*
 * app.c
 *
 *  Created on: May 24, 2023
 *      Author: mohah
 */

#include "HAL/keypad/keypad.h"
#include "HAL/lcd/lcd.h"

#include <util/delay.h>
#include "avr/io.h"

//#define F_CPU 8000000UL


void main(void){

	uint8 key = 'c';

	LCD_init();
	DDRB |= ( 1 << 0 );


	for(;;){
		LCD_clearScreen();
		LCD_displayString("hello ");
		key = KEYPAD_getPressedKey();
		LCD_displayCharacter(key);

		PORTB ^= ( 1 << 0 );


	}

}

