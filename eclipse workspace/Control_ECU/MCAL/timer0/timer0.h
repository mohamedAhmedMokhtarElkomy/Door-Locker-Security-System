 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/

#ifndef MCAL_TIMER0_TIMER0_H_
#define MCAL_TIMER0_TIMER0_H_

#include "../../std_types.h"
#include "../../common_macros.h"

/*******************************************************************************
 *                         Definitions                             		       *
 *******************************************************************************/

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	NORMAL, PWM_PHASE_CORRECT, CTC, FAST_PWM
}E_Timer0Mode;
typedef struct
{
	E_Timer0Mode mode;
//	ADC_prescaler prescaler;

}TIMER0_configType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TIMER0_init();
void TIMER0_start();
void TIMER0_stop();
void TIMER0_clear();



#endif /* MCAL_TIMER0_TIMER0_H_ */




