/*
 * uart.h
 *
 *  Created on: Oct 24, 2023
 *      Author: subra
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f7xx.h"



void uart_write(USART_TypeDef *USARTx, uint8_t value);
uint8_t uart_read(USART_TypeDef *USARTx);
void uart3_tx_init(void);
void uart3_tx_interrupt_init(void);
void uart3_rxtx_init(void);

#define ISR_TXE (1U<<7)


#endif /* UART_H_ */
