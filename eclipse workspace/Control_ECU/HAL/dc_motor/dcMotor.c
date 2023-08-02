 /******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: dcMotor.c
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/

#include "dcMotor.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/timer0/timer0.h"


//DcMotor_configType config_pwm = {EN_TIMER0_ID, PWM_MAX};

void DcMotor_init(DcMotor_configType *dcMotor){
	GPIO_setupPinDirection(dcMotor->port1_id, dcMotor->pin1_id, PIN_OUTPUT);
	GPIO_setupPinDirection(dcMotor->port2_id, dcMotor->pin2_id, PIN_OUTPUT);

	PWM_T0_init();

}
void DcMotor_rotate(DcMotor_configType *dcMotor, DcMotor_state state, uint8 speedPercentage){

	PWM_T0_setDutyCycle(speedPercentage);

	switch(state){
		case EN_DC_CW:
			GPIO_writePin(dcMotor->port1_id, dcMotor->pin1_id, LOGIC_HIGH);
			GPIO_writePin(dcMotor->port2_id, dcMotor->pin2_id, LOGIC_LOW);

			break;

		case EN_DC_A_CW:
			GPIO_writePin(dcMotor->port1_id, dcMotor->pin1_id, LOGIC_LOW);
			GPIO_writePin(dcMotor->port2_id, dcMotor->pin2_id, LOGIC_HIGH);

			break;
	}
}

void DcMotor_stop(DcMotor_configType *dcMotor){
	GPIO_writePin(dcMotor->port1_id, dcMotor->pin1_id, LOGIC_LOW);
	GPIO_writePin(dcMotor->port2_id, dcMotor->pin2_id, LOGIC_LOW);
}

