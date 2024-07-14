/*
 * tim.h
 *
 *  Created on: Nov 22, 2023
 *      Author: subra
 */

#ifndef TIM_H_
#define TIM_H_


void tim1_1hz_init();
void tim1_1hz_interrupt_init();

#define SR_UIF (1U<<0)


#endif /* TIM_H_ */
