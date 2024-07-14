/*
 * rcc.h
 *
 *  Created on: Oct 24, 2023
 *      Author: subra
 */

#ifndef RCC_H_
#define RCC_H_

#include <stdint.h>
#include "stm32f7xx.h"

void set_ahb1_periph_clock(uint32_t periphs);
void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);
void set_apb1_periph_clock(uint32_t periphs);
void set_apb2_periph_clock(uint32_t periphs);

#endif /* RCC_H_ */
