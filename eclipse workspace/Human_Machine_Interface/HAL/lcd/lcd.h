/*
 * lcd.h
 *
 *  Created on: Apr 29, 2023
 *      Author: Mohamed Ahmed Mokhtar
 */

#ifndef LCD_H_
#define LCD_H_

#include "../../std_types.h"

#define LCD_DATA_BITS_MODE 8

#define LCD_RS_PORT		PORTD_ID
#define LCD_RS_PIN		PIN6_ID
#define LCD_E_PORT		PORTD_ID
#define LCD_E_PIN		PIN7_ID
#define LCD_DATA_PORT	PORTC_ID

#define LCD_CMD_CLEAR							0x01
#define LCD_CMD_RETURN_HOME						0x02
#define LCD_CMD_SHIFT_CURSOR_LEFT				0x04
#define LCD_CMD_SHIFT_DISPLAY_RIGHT				0x05
#define LCD_CMD_SHIFT_CURSOR_RIGHT				0x06
#define LCD_CMD_SHIFT_DISPLAY_LEFT				0x07
#define LCD_CMD_DISPLAY_OFF_CURSOR_OFF			0x08
#define LCD_CMD_DISPLAY_OFF_CURSOR_ON			0x0A
#define LCD_CMD_DISPLAY_ON_CURSOR_OF			0x0C
#define LCD_CMD_DISPLAY_ON_CURSOR_ON			0x0E
#define LCD_CMD_DISPLAY_ON_CURSOR_BLINKING		0x0F
#define LCD_CMD_SHIFT_CURSOR_POSITION_LEFT		0x10
#define LCD_CMD_SHIFT_CURSOR_POSITION_RIGHT		0x14
#define LCD_CMD_SHIFT_ENTIRE_DISPLAY_LEFT		0x18
#define LCD_CMD_SHIFT_ENTIRE_DISPLAY_RIGHT		0x1C
#define LCD_CMD_FORCE_CURSOR_BEGINNING_1STLINE	0x80
#define LCD_CMD_FORCE_CURSOR_BEGINNING_2NDLINE	0xC0
#define LCD_CMD_2_LINES_8BITS_MODE				0x38

//#define LCD_RS_PORT_ID PORTD_ID
//#define LCD_RS_PIN_ID
//#define LCD_E_PORT_ID
//#define LCD_E_PORT_ID

/*
	RS = 0 ===> command
	RS = 1 ===> data
	E ===> enable screen
*/

void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(const char *str);
void LCD_moveCursor(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str);
void LCD_clearScreen(void);
void LCD_integerToString(int number);
void LCD_floatToString(float number);

#endif /* LCD_H_ */
