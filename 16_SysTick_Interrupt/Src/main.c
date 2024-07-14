#include <stdio.h>
#include "stm32f7xx.h"

#include "uart.h"
#include "led.h"
#include "sys_tick.h"

#define DELAY 50

char ch;
int main()
{
	uart3_rxtx_init();
	systick_1hz_interrupt();

	while(1)
	{

	}


}

static void systick_callback(void)
{
	printf("A second just passed!!!\n\r");
}

void SysTick_Handler(void)
{
	// Call callback function.
	systick_callback();
}

