#include <stdio.h>
#include "stm32f7xx.h"

#include "uart.h"
#include "led.h"
#include "spi.h"

#define TXE (1U<<1)
#define RXNE (1U<<0)

uint8_t tx_buff[] = "Hello from SPI";
uint8_t tx_size = sizeof(tx_buff);
volatile uint8_t tx_idx = 0;

uint8_t rx_buff[sizeof(tx_buff)];
uint8_t rx_size = sizeof(tx_buff);
volatile uint8_t rx_idx = 0;

int main()
{
	// Configure Master SPI device.
	spi1_config();

	// Configure Slave SPI device.
	spi3_config();

	// Enable Slave (RX) SPI.
	spi3_activate();

	// Enable Master (TX) SPI.
	spi1_activate();

	while(1)
	{

	}
}

void spi1_callback(void)
{
	volatile uint8_t *spidr = ((volatile uint8_t *)&SPI1->DR);
	*spidr = tx_buff[tx_idx++];
}

// SPI1 Interrupt Request Handler implementation.
void SPI1_IRQHandler(void)
{
	// Check TXE flag value in ISR register.
	if((SPI1->SR & TXE))
	{
		// Call callback function.
		spi1_callback();
	}
}

void spi3_callback(void)
{
	rx_buff[rx_idx++] = SPI3->DR;
}

// SPI3 Interrupt Request Handler implementation.
void SPI3_IRQHandler(void)
{
	// Check RXNE flag value in ISR register.
	if((SPI3->SR & RXNE))
	{
		// Call callback function.
		spi3_callback();
	}
}
