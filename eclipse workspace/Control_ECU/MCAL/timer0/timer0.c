/*
 * timer.c
 *
 *  Created on: May 24, 2023
 *      Author: mohah
 */

#include "timer0.h"
#include "avr/io.h"
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void TIMER0_init(){
	CLEAR_BIT(TCCR0, FOC0); /* FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode */
	/***************
	 *WGM01 | WGM00* TCCR0
	 *  0   |   0  * Normal
	 *  0   |   1  * PWM, phase correct
	 *  1   |   0  * CTC
	 *  1   |   1  * Fast PWM
	 ***************/
}
void TIMER0_start(){}
void TIMER0_stop(){}
void TIMER0_clear(){}



void PWM_T0_init(){

	DDRB |= ( 1 << PB3 );
	TCNT0 = 0;
	TCCR0 |= ( 1 << WGM00 ) | ( 1 << WGM01 ) | ( 1 << CS01 ); /* F_PWM=(F_CPU)/(256*N) = (8*10^6)/(256*8) = 4kHz*/
	TCCR0 |= ( 1 << COM01 );
	OCR0 = 255;

}

void PWM_T0_setDutyCycle(uint8 dutyCycle){

	uint16 temp_dutyCycle = (dutyCycle * 255) / 100;

	OCR0 = temp_dutyCycle;
}
