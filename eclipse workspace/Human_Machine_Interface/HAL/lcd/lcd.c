/*
 * lcd.c
 *
 *  Created on: Apr 29, 2023
 *      Author: mohah
 */

#include "lcd.h"
#include "../../MCAL/gpio/gpio.h"
#include <util/delay.h>


void LCD_init(){

	GPIO_setupPinDirection(LCD_RS_PORT, LCD_RS_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT, LCD_E_PIN, PIN_OUTPUT);

	_delay_ms(20);		/* LCD Power ON delay always > 15ms */

#if(LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
	LCD_sendCommand(LCD_CMD_2_LINES_8BITS_MODE);
#endif

	LCD_sendCommand(LCD_CMD_DISPLAY_ON_CURSOR_OF);
	LCD_sendCommand(LCD_CMD_CLEAR);

}
void LCD_sendCommand(uint8 command){
	//Clear RS
	GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_LOW);

	_delay_ms(1);

	//SET E
	GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);

	_delay_ms(1);


	GPIO_writePort(LCD_DATA_PORT, command);

	_delay_ms(1);

	//CLEAR E
	GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);

	_delay_ms(1);

}
void LCD_displayCharacter(uint8 character){
	//Set RS
	GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_HIGH);

	_delay_ms(1);

	//SET E
	GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);

	_delay_ms(1);


	GPIO_writePort(LCD_DATA_PORT, character);

	_delay_ms(1);

	//CLEAR E
	GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);

	_delay_ms(1);

}
void LCD_displayString(const char *str){
	uint8 i = 0;
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}
void LCD_moveCursor(uint8 row, uint8 col){
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	LCD_sendCommand(lcd_memory_address | LCD_CMD_FORCE_CURSOR_BEGINNING_1STLINE);
}
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str){
	LCD_moveCursor(row, col);
	LCD_displayString(str);
}
void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CMD_CLEAR);
}
void LCD_integerToString(int number){
	char buff[16]; /* String to hold the ascii result */
	itoa(number,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff); /* Display the string */
}

void LCD_floatToString(float number){
	char buff[16]; /* String to hold the ascii result */
	dtostrf(number, 3, 2, buff);
	LCD_displayString(buff); /* Display the string */
}
