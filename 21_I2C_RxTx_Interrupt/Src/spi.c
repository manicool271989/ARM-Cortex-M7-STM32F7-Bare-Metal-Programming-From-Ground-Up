/*
 * spi.c
 *
 *  Created on: Jan 7, 2024
 *      Author: subra
 */

#include "spi.h"

#define GPIOAEN	(1U<<0)
#define GPIOBEN (1U<<1)
#define SPI1EN (1U<<12)
#define SPI3EN (1U<<15)

void spi1_config(void)
{
	// Configure GPIOs related to SPI1 pins.
	// Enable clock access to GPIOA.
	RCC->AHB1ENR |= GPIOAEN;

	// Configure SPI1 SCK pin PA5 as alternate function.
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	// Select alternate function type as AF5.
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	// Set pin speed to very high.
	GPIOA->OSPEEDR |= (1U<<10);
	GPIOA->OSPEEDR |= (1U<<11);

	// Enable internal pull-down register.
	GPIOA->PUPDR &= ~(1U<<10);
	GPIOA->PUPDR |= (1U<<11);

	// Configure SPI1 MOSI pin PA7 as alternate function.
	GPIOA->MODER &= ~(1U<<14);
	GPIOA->MODER |= (1U<<15);

	// Select alternate function type as AF5
	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &= ~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &= ~(1U<<31);

	// Set pin speed to very high.
	GPIOA->OSPEEDR |= (1U<<14);
	GPIOA->OSPEEDR |= (1U<<15);

	// Enable internal pull-down register.
	GPIOA->PUPDR &= ~(1U<<14);
	GPIOA->PUPDR |= (1U<<15);

	// Enable SPI1 interrupt in NVIC.
	NVIC_EnableIRQ(SPI1_IRQn);


	// Configure SPI1 communication.
	// Enable clock access to SPI1.
	RCC->APB2ENR |= SPI1EN;

	// Configure the clock of SPI1 by setting the baud rate. Set baud rate to be peripheral clock frequency divided by 256.
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 |= (1U<<4);
	SPI1->CR1 |= (1U<<5);

	// Enable TX only for SPI1 by configuring BIDIMODE and BIDIOE.
	SPI1->CR1 |= (1U<<15); // BIDIMODE set to 1-line bidirectional mode. Needed for half-duplex communication.
	SPI1->CR1 |= (1U<<14); // BIDIOE set to output enabled (transmit-only mode).

	// Set clock polarity and clock phase.
	SPI1->CR1 |= (1U<<0);
	SPI1->CR1 |= (1U<<1);

	// Set the data width. Configure to be 8-bits wide.
	SPI1->CR2 |= (1<<8);
	SPI1->CR2 |= (1<<9);
	SPI1->CR2 |= (1<<10);
	SPI1->CR2 &= ~(1<<11);

	// Set software slave management.
	SPI1->CR1 |= (1U<<9);

	// Set slave select output to enabled.
	SPI1->CR2 |= (1U<<2);

	// Set FIFO reception threshold. Threshold at which RXNE will be triggered.
	SPI1->CR2 |= (1U<<12);

	// Enable TXE interrupt.
	SPI1->CR2 |= (1U<<7);

	// Enable Master mode.
	SPI1->CR1 |= (1U<<2);
}

void spi3_config(void)
{
	// Configure GPIOs related SPI3 pins.
	// Enable clock access to GPIOB.
	RCC->AHB1ENR |= GPIOBEN;

	// Configure SPI3 SCK pin PB3 as alternate function.
	GPIOB->MODER &= ~(1U<<6);
	GPIOB->MODER |= (1U<<7);

	// Set alternate function type as AF6.
	GPIOB->AFR[0] &= ~(1U<<12);
	GPIOB->AFR[0] |= (1U<<13);
	GPIOB->AFR[0] |= (1U<<14);
	GPIOB->AFR[0] &= ~(1U<<15);

	// Set pin speed to very high.
	GPIOB->OSPEEDR |= (1U<<6);
	GPIOB->OSPEEDR |= (1U<<7);

	// Enable internal pull-down register.
	GPIOB->PUPDR &= ~(1U<<6);
	GPIOB->PUPDR |= (1U<<7);

	// Configure SPI3 MISO pin PB4 as alternate function.
	GPIOB->MODER &= ~(1U<<8);
	GPIOB->MODER |= (1U<<9);

	// Set alternate function type as AF6.
	GPIOB->AFR[0] &= ~(1U<<16);
	GPIOB->AFR[0] |= (1U<<17);
	GPIOB->AFR[0] |= (1U<<18);
	GPIOB->AFR[0] &= ~(1U<<19);

	// Set pin speed to very high.
	GPIOB->OSPEEDR |= (1U<<8);
	GPIOB->OSPEEDR |= (1U<<9);

	// Enable internal pull-down register.
	GPIOB->PUPDR &= ~(1U<<8);
	GPIOB->PUPDR |= (1U<<9);

	// Enable SPI3 interrupt in NVIC.
	NVIC_EnableIRQ(SPI3_IRQn);


	// Configure SPI3 communication.
	// Enable clock access to SPI3.
	RCC->APB1ENR |= SPI3EN;

	// Configure the clock of SPI3 by setting the baud rate. Set baud rate to be peripheral clock frequency divided by 256.
	SPI3->CR1 |= (1U<<3);
	SPI3->CR1 |= (1U<<4);
	SPI3->CR1 |= (1U<<5);

	// Set clock polarity and clock phase.
	SPI3->CR1 |= (1U<<0);
	SPI3->CR1 |= (1U<<1);

	// Set the data width. Configure to be 8-bits wide.
	SPI3->CR2 |= (1<<8);
	SPI3->CR2 |= (1<<9);
	SPI3->CR2 |= (1<<10);
	SPI3->CR2 &= ~(1<<11);

	// Set software slave management.
	SPI3->CR1 |= (1U<<9);

	// Set slave select output to enabled.
	SPI3->CR2 |= (1U<<2);

	// Enable RX only for SPI3 by configuring BIDIMODE and BIDIOE.
	SPI3->CR1 |= (1U<<15); // BIDIMODE set to 1-line bidirectional mode. Needed for half-duplex communication.
	SPI3->CR1 &= ~(1U<<14); // BIDIOE set to output disabled (receive-only mode).

	// Set FIFO reception threshold. Threshold at which RXNE will be triggered.
	SPI3->CR2 |= (1U<<12);

	// Enable RXE interrupt.
	SPI3->CR2 |= (1U<<6);

	// Enable Slave mode.
	//SPI3->CR1 &= ~(1U<<2);


}

void spi1_activate(void)
{
	// Enable SPI1 Peripheral.
	SPI1->CR1 |= (1U<<6);
}

void spi3_activate(void)
{
	// Enable SPI3 Peripheral.
	SPI3->CR1 |= (1U<<6);
}
