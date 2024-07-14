#include <stdio.h>
#include "stm32f7xx.h"

#include "uart.h"
#include "led.h"

char ch;
int main()
{


	all_leds_init();
	uart3_rxtx_init();


	while(1)
	{

		ch = uart_read(USART3);

		switch(ch)
		{
			case '0':
				all_leds_off();
				break;
			case 'a':
				all_leds_on();
				break;
			case 'r':
				led_toggle(red_led);
				break;
			case 'g':
				led_toggle(green_led);
			case 'b':
				led_toggle(blue_led);
		}
	}
}

