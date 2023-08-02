/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/



#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include "../../std_types.h"
#include "../../common_macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TIMER1_MAX_VALUE 				65535U
#define TIMER1_ONE_SECOND_CLK_256_8M 	31250U /* number of ticks needed to count one second with 256 prescaler */
#define TIMER1_ONE_SECOND_CLK_1024_8M 	7812U /* 7812.5 to be one second so CLK_256 is more accurate */ /* number of ticks needed to count one second with 256 prescaler */
//#define CALCULATE_ONE_SECOND_TICKS(PRE_SCALER) F_CPU / PRE_SCALER

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */
extern volatile uint16 count;


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum {TIMER1_NO_CLK_SRC = 0, TIMER1_CLK_1, TIMER1_CLK_8,
	TIMER1_CLK_64, TIMER1_CLK_256, TIMER1_CLK_1024,
	TIMER1_CLK_EXT_FALLING, TIMER1_CLK_EXT_RISING
} EN_timer1_prescaler;

typedef enum {
	TIMER1_NORMAL
} EN_timer1_mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 EN_timer1_prescaler prescaler;
 EN_timer1_mode mode;
} ST_timer1_configType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


void Timer1_init(const ST_timer1_configType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));




#endif /* MCAL_TIMER_TIMER_H_ */
