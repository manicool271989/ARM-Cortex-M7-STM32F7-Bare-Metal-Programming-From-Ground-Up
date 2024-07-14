/*
 * tim.c
 *
 *  Created on: Nov 22, 2023
 *      Author: subra
 */

#include "stm32f7xx.h"

#define TIM1EN (1U<<0)

void tim1_1hz_init()
{
	// Enable clock access to Timer.
	RCC->APB1ENR |= TIM1EN;

	// Set Prescalar Value

	// Set Auto-Reload Reg Value
	// Enable Timer
}
