/*
 * sys_tick.c
 *
 *  Created on: Nov 20, 2023
 *      Author: subra
 */

#include "stm32f7xx.h"

#define SYSTICK_LOAD_VAL 16000
#define CTRL_CLKSRC (1U<<2)
#define CTRL_ENABLE (1U<<0)
#define CTRL_COUNTFLAG (1U<<16)

void systickDelay(int delay)
{
	// Load the # of cycles to count down from.
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// Clear the current value register.
	SysTick->VAL = 0;

	// Set the clock source and enable the SysTick timer.
	SysTick->CTRL |= CTRL_CLKSRC | CTRL_ENABLE;

	// Wait through the SysTick timer by delay number of times.
	for(int i = 0; i < delay; i++)
	{
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0)
		{
		}
	}

	// Disable SysTick
	SysTick->CTRL = 0;

}
