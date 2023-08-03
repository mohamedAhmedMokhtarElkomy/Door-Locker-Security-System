/*
 * eeprom.h
 *
 *  Created on: Aug 3, 2023
 *      Author: mohah
 */

#ifndef HAL_EEPROM_EEPROM_H_
#define HAL_EEPROM_EEPROM_H_

#include "../../std_types.h"

#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
//uint8 EEPROM_writeData(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* HAL_EEPROM_EEPROM_H_ */
