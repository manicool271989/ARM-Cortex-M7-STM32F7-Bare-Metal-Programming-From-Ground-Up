
#include <stdio.h>
#include "stm32f7xx.h"

#define		GPIODEN					(1U<<3)
#define		UART3_TX				(1U<<8)
#define		GPIO_ALTERNATE_MODE 	0x2

#define 	USART3EN				(1U<<18)

#define UART_DATAWIDTH_8B			0x00000000U
#define UART_PARITY_NONE			0x00000000U
#define UART_STOPBITS_1				0x00000000U

void set_ahb1_periph_clock(uint32_t periphs);
void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);
void set_apb1_periph_clock(uint32_t periphs);
void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits);
void set_uart_transfer_direction(USART_TypeDef *USARTx, uint32_t TransferDirection);
uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
void uart_set_baudrate(USART_TypeDef *UARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart_enable(USART_TypeDef *UARTx);
void uart3_tx_init(void);
void uart_write(USART_TypeDef *USARTx, uint8_t value);


int main()
{
	int x;
	uart3_tx_init();


	while(1)
	{

		//uart_write(USART3, 'A');
		printf("Hello World from STM32F7!\r");
		for(int i = 0; i < 9000; i++)
		{
			x++;
		}
	}
}

void uart_write(USART_TypeDef *USARTx, uint8_t value)
{
	// Make sure transmit data register is empty
	while (!(USARTx->ISR & USART_ISR_TXE)) {}

	// Write value into transmit data register
	USARTx->TDR = value;

}

int __io_putchar(int ch) {
	uart_write(USART3, ch);
	return ch;
}

void uart3_tx_init(void)
{
	// To get pin ready as USART pin:
	// 1. Enable clock access to GPIOD
	set_ahb1_periph_clock(GPIODEN);

	// 2. Set PD8 mode to alternate function
	set_pin_mode(GPIOD, UART3_TX, GPIO_ALTERNATE_MODE);

	// 3. Set alternate function type to USART
	/*GPIOD->AFR[1] |= (1U<<0);
	GPIOD->AFR[1] |= (1U<<1);
	GPIOD->AFR[1] |= (1U<<2);
	GPIOD->AFR[1] &= ~(1U<<3);*/
	GPIOD->AFR[1]|=0x77;

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

void uart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CR1, USART_CR1_UE);
}

void set_uart_transfer_direction(USART_TypeDef *USARTx, uint32_t TransferDirection)
{
	MODIFY_REG(USARTx->CR1, (USART_CR1_RE |USART_CR1_TE), TransferDirection);
}

void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div(PeriphClk, BaudRate);
}

void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
	MODIFY_REG(USARTx->CR1, (USART_CR1_PS | USART_CR1_PCE | USART_CR1_M), Parity | DataWidth);
	MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}

void set_ahb1_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->AHB1ENR, periphs);
}

void set_ahb2_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->AHB2ENR, periphs);
}

void set_apb1_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->APB1ENR, periphs);
}

void set_apb2_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->APB2ENR, periphs);
}

void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
	// set the relevant bit in the mode register
	// CLEARMASK explanation:
	// 0b 11 << 16 (shift 0b11 to position 16 (LSB occupies bit 16, MSB occupies bit 17))
	MODIFY_REG(GPIOx->MODER, (0x3 << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
}

uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return (PeriphClk + (BaudRate/2U))/BaudRate;
}
