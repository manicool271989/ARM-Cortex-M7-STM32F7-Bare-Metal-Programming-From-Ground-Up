/*
 * uart.c
 *
 *  Created on: Oct 24, 2023
 *      Author: subra
 */

#include "uart.h"
#include "rcc.h"
#include "gpio.h"

#define		UART3_TX				(1U<<8)
#define		UART3_RX				(1U<<9)
#define 	USART3EN				(1U<<18)
#define UART_DATAWIDTH_8B			0x00000000U
#define UART_PARITY_NONE			0x00000000U
#define UART_STOPBITS_1				0x00000000U

#define		GPIODEN					(1U<<3)
#define		GPIO_ALTERNATE_MODE 	0x2

#define CR1_RXNEIE (1U<<5)

void uart_write(USART_TypeDef *USARTx, uint8_t value)
{
	// Make sure transmit data register is empty
	while (!(USARTx->ISR & USART_ISR_TXE)) {}

	// Write value into transmit data register
	USARTx->TDR = value;

}

uint8_t uart_read(USART_TypeDef *USARTx)
{
	// Make sure receive data register has data
	while (!(USARTx->ISR & USART_ISR_RXNE)) {}

	// Read value out of receive data register
	return (READ_BIT(USARTx->RDR, USART_RDR_RDR) & 0xFFU);
}

int __io_putchar(int ch) {
	uart_write(USART3, ch);
	return ch;
}

static void uart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CR1, USART_CR1_UE);
}

static void set_uart_transfer_direction(USART_TypeDef *USARTx, uint32_t TransferDirection)
{
	MODIFY_REG(USARTx->CR1, (USART_CR1_RE |USART_CR1_TE), TransferDirection);
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return (PeriphClk + (BaudRate/2U))/BaudRate;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div(PeriphClk, BaudRate);
}

static void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
	MODIFY_REG(USARTx->CR1, (USART_CR1_PS | USART_CR1_PCE | USART_CR1_M), Parity | DataWidth);
	MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}

void uart3_rx_interrupt_init(void)
{
	// To get pin ready as USART pin:
	// 1. Enable clock access to GPIOD
	set_ahb1_periph_clock(GPIODEN);

	// 2. Set PD8 mode to alternate function
	set_pin_mode(GPIOD, UART3_TX, GPIO_ALTERNATE_MODE);
	// 2a. Set PD9 mode to alternate function
	set_pin_mode(GPIOD, UART3_RX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function type to USART for PD8
	GPIOD->AFR[1] |= (1U<<0);
	GPIOD->AFR[1] |= (1U<<1);
	GPIOD->AFR[1] |= (1U<<2);
	GPIOD->AFR[1] &= ~(1U<<3);
	// 3a. Set alternate function type to USART for PD9
	GPIOD->AFR[1] |= (1U<<4);
	GPIOD->AFR[1] |= (1U<<5);
	GPIOD->AFR[1] |= (1U<<6);
	GPIOD->AFR[1] &= ~(1U<<7);
	//GPIOD->AFR[1]|=0x77;

	// To get USART/UART peripheral ready:
	// Enable clock to USART3 module
	set_apb1_periph_clock(USART3EN);

	// Configure USART parameters
	config_uart_parameters(USART3, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBITS_1);
	set_uart_transfer_direction(USART3, (USART_CR1_TE|USART_CR1_RE));

	// Set baudrate
	uart_set_baudrate(USART3, 16000000, 57600);

	// Enable USART
	//USART3->CR1 |= USART_CR1_UE;
	uart_enable(USART3);

	// Enable UART rxne interrupt.
	USART3->CR1 |= CR1_RXNEIE;

	// Enable UART interrupt in NVIC.
	NVIC_EnableIRQ(USART3_IRQn);
}

void uart3_tx_init(void)
{
	// To get pin ready as USART pin:
	// 1. Enable clock access to GPIOD
	set_ahb1_periph_clock(GPIODEN);

	// 2. Set PD8 mode to alternate function
	set_pin_mode(GPIOD, UART3_TX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function type to USART for PD8
	GPIOD->AFR[1] |= (1U<<0);
	GPIOD->AFR[1] |= (1U<<1);
	GPIOD->AFR[1] |= (1U<<2);
	GPIOD->AFR[1] &= ~(1U<<3);

	// To get USART/UART peripheral ready:
	// Enable clock to USART3 module
	set_apb1_periph_clock(USART3EN);

	// Configure USART parameters
	config_uart_parameters(USART3, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBITS_1);
	set_uart_transfer_direction(USART3, USART_CR1_TE);

	// Set baudrate
	uart_set_baudrate(USART3, 16000000, 57600);

	// Enable USART
	//USART3->CR1 |= USART_CR1_UE;
	uart_enable(USART3);
}

void uart3_rxtx_init(void)
{
	// To get pin ready as USART pin:
	// 1. Enable clock access to GPIOD
	set_ahb1_periph_clock(GPIODEN);

	// 2. Set PD8 mode to alternate function
	set_pin_mode(GPIOD, UART3_TX, GPIO_ALTERNATE_MODE);
	// 2a. Set PD9 mode to alternate function
	set_pin_mode(GPIOD, UART3_RX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function type to USART for PD8
	GPIOD->AFR[1] |= (1U<<0);
	GPIOD->AFR[1] |= (1U<<1);
	GPIOD->AFR[1] |= (1U<<2);
	GPIOD->AFR[1] &= ~(1U<<3);
	// 3a. Set alternate function type to USART for PD9
	GPIOD->AFR[1] |= (1U<<4);
	GPIOD->AFR[1] |= (1U<<5);
	GPIOD->AFR[1] |= (1U<<6);
	GPIOD->AFR[1] &= ~(1U<<7);
	//GPIOD->AFR[1]|=0x77;

	// To get USART/UART peripheral ready:
	// Enable clock to USART3 module
	set_apb1_periph_clock(USART3EN);

	// Configure USART parameters
	config_uart_parameters(USART3, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBITS_1);
	set_uart_transfer_direction(USART3, (USART_CR1_TE|USART_CR1_RE));

	// Set baudrate
	uart_set_baudrate(USART3, 16000000, 57600);

	// Enable USART
	//USART3->CR1 |= USART_CR1_UE;
	uart_enable(USART3);
}
