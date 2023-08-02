/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: BUZZER.c
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/

#include "buzzer.h"
#include "avr/io.h"
#include "../../common_macros.h"
#include "../../MCAL/gpio/gpio.h"
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

void Buzzer_init(){
	GPIO_setupPinDirection(buzzer_port, buzzer_pin, PIN_OUTPUT);
}
void Buzzer_on(void){
	GPIO_writePin(buzzer_port, buzzer_pin, LOGIC_HIGH);
}
void Buzzer_off(void){
	GPIO_writePin(buzzer_port, buzzer_pin, LOGIC_LOW);
}
