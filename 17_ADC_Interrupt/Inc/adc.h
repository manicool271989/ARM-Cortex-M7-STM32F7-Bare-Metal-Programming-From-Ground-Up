/*
 * adc.h
 *
 *  Created on: Nov 4, 2023
 *      Author: subra
 */

#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"
#include "stm32f7xx.h"

#define EOC (1U<<1)

void pa4_adc_init(void);
void pa4_adc_interrupt_init(void);
uint32_t adc_get_data(void);


#endif /* ADC_H_ */
