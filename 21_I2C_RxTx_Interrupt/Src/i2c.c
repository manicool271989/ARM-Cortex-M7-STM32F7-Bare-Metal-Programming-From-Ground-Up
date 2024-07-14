/*
 * i2c.c
 *
 *  Created on: Jan 15, 2024
 *      Author: subra
 */

#include "i2c.h"

#define GPIOBEN (1U<<1)
#define I2C2EN (1U<<22)
#define I2C1EN (1U<<21)

#define I2C_TIMING 0x00303D5B

static void i2c2_setOwnAddress1(uint32_t OwnAddress1, uint32_t OwnAddrSize);

void i2c2_slave_config(void)
{
	// Configure GPIO pins.
	// Enable clock access to GPIOB (so that we can use PB10, PB11 pins).
	RCC->AHB1ENR |= GPIOBEN;

	// Configure PB10, PB11 as alternate function pins.
	// PB10
	GPIOB->MODER &= ~(1U<<20);
	GPIOB->MODER |= (1U<<21);
	// PB11
	GPIOB->MODER &= ~(1U<<22);
	GPIOB->MODER |= (1U<<23);

	// Configure the alternate function type as AF4.
	// PB10
	GPIOB->AFR[1] &= ~(1U<<8);
	GPIOB->AFR[1] &= ~(1U<<9);
	GPIOB->AFR[1] |= (1U<<10);
	GPIOB->AFR[1] &= ~(1U<<11);
	// PB11
	GPIOB->AFR[1] &= ~(1U<<12);
	GPIOB->AFR[1] &= ~(1U<<13);
	GPIOB->AFR[1] |= (1U<<14);
	GPIOB->AFR[1] &= ~(1U<<15);

	// Configure pins as open-drain.
	// PB10
	GPIOB->OTYPER |= (1U<<10);
	// PB11
	GPIOB->OTYPER |= (1U<<11);

	// Configure pins to have pull-up resistors.
	// PB10
	GPIOB->PUPDR |= (1U<<20);
	GPIOB->PUPDR &= ~(1U<<21);
	// PB11
	GPIOB->PUPDR |= (1U<<22);
	GPIOB->PUPDR &= ~(1U<<23);


	// Configure I2C parameters (slave).
	// Enable clock access to I2C2.
	RCC->APB1ENR |= I2C2EN;

	// Enable I2C2 interrupts in NVIC.
	NVIC_EnableIRQ(I2C2_EV_IRQn);

	// Disable I2C2 before configuring the module.
	I2C2->CR1 &= ~(1U<<0);

	// Set Own Address since this is the slave I2C module.
	i2c2_setOwnAddress1(SLAVE_OWN_ADDRESS, 0);

	// Enable Own Address.
	I2C2->OAR1 |= (1U<<15);

	// Enable I2C2.
	I2C2->CR1 |= (1U<<0);


	// Enable address (ADDR) interrupt.
	I2C2->CR1 |= (1U<<3);

	// Enable NACK interrupt.
	I2C2->CR1 |= (1U<<4);

	// Enable STOP interrupt.
	I2C2->CR1 |= (1U<<5);

}

static void i2c2_setOwnAddress1(uint32_t OwnAddress1, uint32_t OwnAddrSize)
{
	// Configure own address mode to be 7-bit addressing and set the own address bits for this example.
	MODIFY_REG(I2C2->OAR1, I2C_OAR1_OA1 | I2C_OAR1_OA1MODE, OwnAddress1 | OwnAddrSize);
}

void i2c1_master_config(void)
{
	// Configure GPIO pins.
	// Enable clock access to GPIOB (so that we can use PB8, PB9 pins).
	RCC->AHB1ENR |= GPIOBEN;

	// Configure PB8, PB9 as alternate function pins.
	// PB8
	GPIOB->MODER &= ~(1U<<16);
	GPIOB->MODER |= (1U<<17);
	// PB9
	GPIOB->MODER &= ~(1U<<18);
	GPIOB->MODER |= (1U<<19);

	// Configure the alternate function type as AF4.
	// PB8
	GPIOB->AFR[1] &= ~(1U<<0);
	GPIOB->AFR[1] &= ~(1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &= ~(1U<<3);
	// PB9
	GPIOB->AFR[1] &= ~(1U<<4);
	GPIOB->AFR[1] &= ~(1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &= ~(1U<<7);

	// Configure pins as open-drain.
	// PB8
	GPIOB->OTYPER |= (1U<<8);
	// PB9
	GPIOB->OTYPER |= (1U<<9);

	// Configure pins to have pull-up resistors.
	// PB8
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &= ~(1U<<17);
	// PB9
	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &= ~(1U<<19);


	// Configure I2C1 parameters (master). Master is configured to be working in polling mode so no interrupts are enabled.
	// Enable clock access to I2C1.
	RCC->APB1ENR |= I2C1EN;

	// Enable I2C1 interrupts in NVIC.
	NVIC_EnableIRQ(I2C1_EV_IRQn);

	// Disable I2C1 before configuring the module.
	I2C1->CR1 &= ~(1U<<0);

	// Set the I2C1 Timing register.
	I2C1->TIMINGR = I2C_TIMING;

	// Enable I2C1.
	I2C1->CR1 |= (1U<<0);

}

uint32_t i2c2_get_address_matchcode(void)
{
	return (uint32_t) (READ_BIT(I2C2->ISR, I2C_ISR_ADDCODE) >> I2C_ISR_ADDCODE_Pos << 1);
}
