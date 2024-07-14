#include <stdio.h>
#include "stm32f7xx.h"

#include "uart.h"
#include "led.h"
#include "sys_tick.h"
#include "tim.h"

#define DELAY 50

char ch;
int main()
{
	uart3_rxtx_init();

	while(1)
	{

	}


}

