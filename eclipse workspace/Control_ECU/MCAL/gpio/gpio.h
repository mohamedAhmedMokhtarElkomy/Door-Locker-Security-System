  /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description:
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../../std_types.h"
#include "../../common_macros.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

typedef enum{
    GPIO_PIN_INPUT, GPIO_PIN_OUTPUT
}GPIO_PIN_DIRECTION;

typedef enum{
    GPIO_PORT_INPUT = 0x00, GPIO_PORT_OUTPUT = 0xFF
}GPIO_PORT_DIRECTION;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, uint8 direction);
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);
void GPIO_togglePin(uint8 port_num, uint8 pin_num);

void GPIO_setupPortDirection(uint8 port_num, uint8 direction);
void GPIO_writePort(uint8 port_num, uint8 value);
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
