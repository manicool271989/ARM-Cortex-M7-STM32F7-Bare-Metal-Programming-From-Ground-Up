/*
 * adc.c
 *
 *  Created on: Nov 4, 2023
 *      Author: subra
 */
#include "adc.h"

#define GPIOAEN (1U<<0)
#define ADC1EN 	(1U<<8)
#define ADC1CONT (1U<<1)
#define ADCON (1U<<0)
#define CH4_RANK1 (1U<<2)
#define SWSTART (1U<<30)


#define CR1_EOCIE (1U<<5)

void pa4_adc_init(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Configure GPIOA pin (PA4) mode to analog mode
	GPIOA->MODER |= (1U<<9) | (1U<<8);

	// Enable clock access to ADC1
	RCC->APB2ENR |= ADC1EN;

	// Configure ADC1
	// Set conversion mode
	ADC1->CR2 |= ADC1CONT;

	// Set sequencer length
	ADC1->SQR1 = 0;

	// Set ADC channel
	ADC1->SQR3 |= CH4_RANK1;

	// Enable ADC
	ADC1->CR2 |= ADCON;

	// Start conversion
	ADC1->CR2 |= SWSTART;
}

void pa4_adc_interrupt_init(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Configure GPIOA pin (PA4) mode to analog mode
	GPIOA->MODER |= (1U<<9) | (1U<<8);

	// Enable clock access to ADC1
	RCC->APB2ENR |= ADC1EN;

	// Configure ADC1
	// Set conversion mode
	ADC1->CR2 |= ADC1CONT;

	// Set sequencer length
	ADC1->SQR1 = 0;

	// Set ADC channel
	ADC1->SQR3 |= CH4_RANK1;

	// Enable ADC
	ADC1->CR2 |= ADCON;

	// Enable ADC End of Conversion Interrupt.
	ADC1->CR1 |= CR1_EOCIE;

	// Enable ADC Interrupt in NVIC.
	NVIC_EnableIRQ(ADC_IRQn);

	// Start conversion
	ADC1->CR2 |= SWSTART;
}


uint32_t adc_get_data(void)
{
	// Wait for end-of-conversion flag
	if (!(ADC1->SR & EOC)) {}

	// Read results
	return (ADC1->DR);

}
