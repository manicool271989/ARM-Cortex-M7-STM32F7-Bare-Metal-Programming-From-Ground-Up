/*
 * tim.c
 *
 *  Created on: Nov 22, 2023
 *      Author: subra
 */

#include "stm32f7xx.h"

#define TIM1EN (1U<<0)
#define CR1_CEN (1U<<0)
#define DIER_UIE (1U<<0)
#define EGR_UG (1U<<0)

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

void tim1_1hz_interrupt_init()
{
	// Enable clock access to Timer.
	RCC->APB2ENR |= TIM1EN;

	// Set Prescalar Value
	TIM1->PSC = 1600 - 1;

	// Set Auto-Reload Reg Value
	TIM1->ARR = 10000 - 1;

	// Enable TIM1 update interrupt.
	TIM1->DIER |= DIER_UIE;

	// Enable TIM1 update interrupt in NVIC.
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	// Enable Timer
	TIM1->CR1 |= CR1_CEN;

	// Force update generation.
	TIM1->EGR |= EGR_UG;
}
