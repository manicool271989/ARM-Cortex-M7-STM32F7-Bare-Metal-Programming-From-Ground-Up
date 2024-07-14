/*
 * led.h
 *
 *  Created on: Nov 1, 2023
 *      Author: subra
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f7xx.h"
#include <stdint.h>

#define GPIOB_CLK_EN	(1U<<1) // Shifting 1 to postion 1. Example: (1U<<5) 0000 0000 -> 0001 0000

#define USER_LED1_MODER0	(1U<<0)  // Set bit 0 to 1.
#define USER_LED1_MODER1	(1U<<1)  // Set bit 1 to 0.
#define USER_LED2_MODER0	(1U<<14) // Set bit 14 to 1.
#define USER_LED2_MODER1	(1U<<15) // Set bit 15 to 0.
#define USER_LED3_MODER0	(1U<<28) // Set bit 28 to 1.
#define USER_LED3_MODER1	(1U<<29) // Set bit 29 to 0.

#define USER_LED1 (1U<<0)  // green led
#define USER_LED2 (1U<<7)  // blue led
#define USER_LED3 (1U<<14) // red led

#define green_led USER_LED1
#define blue_led USER_LED2
#define red_led USER_LED3

typedef uint32_t ledType;


void all_leds_init(void);
void all_leds_on(void);
void all_leds_off(void);
void all_leds_toggle(void);
void led_on(ledType led);
void led_off(ledType led);
void led_toggle(ledType led);


#endif /* LED_H_ */
