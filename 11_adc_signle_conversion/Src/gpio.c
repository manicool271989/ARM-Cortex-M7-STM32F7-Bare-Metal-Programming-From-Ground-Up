/*
 * gpio.c
 *
 *  Created on: Oct 24, 2023
 *      Author: subra
 */

#include <gpio.h>

void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
	// set the relevant bit in the mode register
	// CLEARMASK explanation:
	// 0b 11 << 16 (shift 0b11 to position 16 (LSB occupies bit 16, MSB occupies bit 17))
	MODIFY_REG(GPIOx->MODER, (0x3 << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
}
