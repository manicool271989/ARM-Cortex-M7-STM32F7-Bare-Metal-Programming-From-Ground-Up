/*
 * tim.c
 *
 *  Created on: Nov 22, 2023
 *      Author: subra
 */

#include "stm32f7xx.h"

#define TIM1EN (1U<<0)
#define CR1_CEN (1U<<0)

void tim1_1hz_init()
{
	// Enable clock access to Timer.
	RCC->APB2ENR |= TIM1EN;

	// Set Prescalar Value
	TIM1->PSC = 1600 - 1;

	// Set Auto-Reload Reg Value
	TIM1->ARR = 10000 - 1;

	// Enable Timer
	TIM1->CR1 |= CR1_CEN;
}
