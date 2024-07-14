#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"

static void adc_conversion_complete_callback(void);

int sensor_value;

int main(void)
{
	uart3_tx_init();

	pa4_adc_interrupt_init();


	while(1)
	{

	}

}

static void adc_conversion_complete_callback(void)
{
	sensor_value = ADC1->DR;
	printf("sensor value : %d \n\r", sensor_value);
}

void ADC_IRQHandler(void)
{
	// Check if End-of-Conversion Interrupt occurred by checking the End-of-Conversion flag in the ADC Status Register.
	if((ADC1->SR & EOC) == EOC)
	{
		// Clear the flag.
		ADC1->SR &= ~EOC;
		// Do something.
		adc_conversion_complete_callback();
	}
}
