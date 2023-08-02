 /******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: dcMotor.h
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/

#ifndef ECUAL_DCMOTOR_DCMOTOR_H_
#define ECUAL_DCMOTOR_DCMOTOR_H_

#include "../../std_types.h"

typedef enum{
	EN_DC_STOP, EN_DC_CW, EN_DC_A_CW
}DcMotor_state;

typedef struct
{
	uint8 port1_id;
	uint8 port2_id;
	uint8 pin1_id;
	uint8 pin2_id;

}DcMotor_configType;

void DcMotor_init(DcMotor_configType *dcMotor);
void DcMotor_rotate(DcMotor_configType *dcMotor, DcMotor_state state, uint8 speed);
void DcMotor_stop(DcMotor_configType *dcMotor);

#endif /* ECUAL_DCMOTOR_DCMOTOR_H_ */
