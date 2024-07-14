/*
 * gpio.h
 *
 *  Created on: Oct 24, 2023
 *      Author: subra
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "stm32f7xx.h"

void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);

#endif /* GPIO_H_ */
