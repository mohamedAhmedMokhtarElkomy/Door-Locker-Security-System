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

	//TODO make TWBR dynamic
	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	TWBR = 0x02;
	TWSR = 0x00;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
   	   General Call Recognition: Off */
	TWAR = 0b00000010; // my address = 0x01 address from BIT 7..1

	TWCR = (1 << TWINT) | ( TWEN << 1);

}
void TWI_start(){

	TWCR = (1 << TWINT) | ( TWSTA << 1) | ( TWEN << 1);
	while( BIT_IS_CLEAR(TWCR, TWINT) ); //wait until TWI finish its process
}

void TWI_stop(){
	TWCR = (1 << TWINT) | ( TWSTO << 1) | ( TWEN << 1);
}
void TWI_writeByte(){}
uint8 TWI_readByteWithACK(){}
uint8 TWI_readByteWithNACK(){}

uint8 TWI_getStatus(){
	return ( TWSR & 0xF8 );
}
