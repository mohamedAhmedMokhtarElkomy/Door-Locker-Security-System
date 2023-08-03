/******************************************************************************
 *
 * Module: TWI
 *
 * File Name: TWI.c
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/

#include "i2c.h"
#include "avr/io.h"
#include "../../common_macros.h"
#include "../gpio/gpio.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void TWI_init(){

	TWAR = 0b00000010; // my address = 0x01 address from BIT 7..1

	TWSR = 0x00; /* set Prescaler and clear old status*/

	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	TWBR = BITRATE(TWSR); /* set baud rate */

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
   	   General Call Recognition: Off */


//	TWCR = ( 1 << TWEN);

}
void TWI_start(){

	TWCR = (1 << TWINT) | ( 1 << TWSTA) | ( 1 << TWEN);
	while( BIT_IS_CLEAR(TWCR, TWINT) ); //wait until TWI finish its process
}

void TWI_stop(){
	TWCR = (1 << TWINT) | ( 1 << TWSTO ) | ( 1 << TWEN);
//	while( BIT_IS_CLEAR(TWCR, TWINT) ); //wait until TWI finish its process

}
void TWI_writeByte(uint8 data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(BIT_IS_CLEAR(TWCR,TWINT));
}
uint8 TWI_readByteWithACK(){
   TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}
uint8 TWI_readByteWithNACK(){
	TWCR = (1 << TWINT) | (1 << TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 TWI_getStatus(){
	return ( TWSR & 0xF8 );
}
