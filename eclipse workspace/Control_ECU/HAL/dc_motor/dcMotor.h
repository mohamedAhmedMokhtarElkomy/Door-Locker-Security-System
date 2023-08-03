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
}EN_dcMotor_state;

typedef struct
{
	uint8 port1_id;
	uint8 port2_id;
	uint8 pin1_id;
	uint8 pin2_id;

}ST_dcMotor_configType;

void DcMotor_init(ST_dcMotor_configType *dcMotor);
void DcMotor_rotate(ST_dcMotor_configType *dcMotor, EN_dcMotor_state state, uint8 speed);
void DcMotor_stop(ST_dcMotor_configType *dcMotor);

#endif /* ECUAL_DCMOTOR_DCMOTOR_H_ */
