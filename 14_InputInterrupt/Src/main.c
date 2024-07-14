#include <stdio.h>
#include "stm32f7xx.h"

#include "uart.h"
#include "led.h"
#include "sys_tick.h"
#include "tim.h"
#include "exti.h"

#define DELAY 50

char ch;
int main()
{
	uart3_rxtx_init();
	all_leds_init();
	pc13_exti_init();

	while(1)
	{

	}


}

static void user_btn_callback(void)
{
	all_leds_toggle();
	printf("BTN Pressed...\n\r");
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR != 0)
	{
		// Clear PR Flag to re arm the interrupt.
		EXTI->PR |= PIN13;

		// Do something
		user_btn_callback();
	}
}

