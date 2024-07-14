#include <stdio.h>
#include "stm32f7xx.h"

#include "uart.h"
#include "led.h"
#include "sys_tick.h"
#include "tim.h"
#include "exti.h"


int main()
{
	uart3_rxtx_init();
	all_leds_init();

	tim1_1hz_interrupt_init();

	while(1)
	{

	}


}

static void tim1_update_callback(void)
{
	all_leds_toggle();
	printf("One second has passed!!!\n\r");
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	// Check if the update interrupt is pending.
	if((TIM1->SR & SR_UIF) != 0)
	{
		// Clear the update interrupt flag.
		TIM1->SR &= ~SR_UIF;
		// Call callback function.
		tim1_update_callback();
	}
}

