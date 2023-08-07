/*
 * timer.c
 *
 *  Created on: Aug 2, 2023
 *      Author: mohah
 */


#include "timer.h"
#include<avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                          Private Variables                                  *
 *******************************************************************************/
uint16 tcnt1_value = 0 ; /* To store TCNT1 value from configPtr in init function */
uint8 seconds_count = 0;

void (*callBackFunction)();


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
volatile uint16 count = 0;


/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
ISR(TIMER1_OVF_vect){

	(*callBackFunction)();
	TCNT1 = tcnt1_value;

}


void Timer1_init(const ST_timer1_configType * Config_Ptr){

	tcnt1_value = Config_Ptr->initial_value;


	TCNT1 = tcnt1_value;
	TCCR1B |= ( 0x07 & Config_Ptr->prescaler );
	SET_BIT(TIMSK, TOIE1);	/* Overflow Interrupt Enable */


}
void Timer1_deInit(void){
	TCNT1 = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	CLEAR_BIT(TIMSK, TOIE1);
}

void Timer1_setCallBack(void(*a_ptr)(void)){

	callBackFunction = a_ptr;
}
