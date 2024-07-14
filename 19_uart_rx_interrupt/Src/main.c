#include <stdio.h>
#include "stm32f7xx.h"

#include "uart.h"
#include "led.h"

char ch;
int main()
{


	all_leds_init();
	uart3_rx_interrupt_init();


	while(1)
	{
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

static void uart_rx_callback(void)
{
	ch = (READ_BIT(USART3->RDR, USART_RDR_RDR) & 0xFFU);
}

void USART3_IRQHandler(void)
{
	// Check if rxne interrupt occurred.
	if((USART3->ISR & ISR_RXNE) == ISR_RXNE)
	{
		uart_rx_callback();
	}
}

