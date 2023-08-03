 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C.h
 *
 * Author: Mohamed Ahmed Mokhtar
 *
 *******************************************************************************/

#ifndef TWI_H_
#define TWI_H_




#include "../../std_types.h"
#include <math.h>
/*******************************************************************************
 *                         Definitions                             		       *
 *******************************************************************************/
#define SCL_CLK 400000U

//#define BITRATE(TWSR) (( F_CPU/SCL_CLK) - 16 ) / ( 2 * pow( 4,( TWSR&(( 1 << TWPS0 ) | ( 1 << TWPS1) ))))

#define BITRATE(TWSR) 0x02

#define TWI_START_STATE				0x08
#define	TWI_REPEATED_START_STATE	0x10
#define	TWI_SLA_W_ACK_STATE			0x18
#define TWI_SLA_W_NACK_STATE		0x20
#define TWI_SLA_R_ACK_STATE			0x40
#define TWI_SLA_R_NACK_STATE		0x48
#define	TWI_DATA_WRITE_ACK_STATE	0x28
#define TWI_DATA_WRITE_NACK_STATE	0x30
#define TWI_DATA_READ_ACK_STATE		0x50
#define TWI_DATA_READ_NACK_STATE	0x58

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TWI_init();
void TWI_start();
void TWI_stop();
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK();
uint8 TWI_readByteWithNACK();
uint8 TWI_getStatus();

#endif
