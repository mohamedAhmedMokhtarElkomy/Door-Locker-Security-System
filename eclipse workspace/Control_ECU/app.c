/*
 * app.c
 *
 *  Created on: May 24, 2023
 *      Author: mohah
 */

#include "MCAL/uart/uart.h"


#include <string.h>
#include "avr/io.h"
#include <util/delay.h>


void setup(){
	UART_init();
}

void main(void){


//	if(strcmp(password, confirmation_password) == 0){return;}

	setup();



}

