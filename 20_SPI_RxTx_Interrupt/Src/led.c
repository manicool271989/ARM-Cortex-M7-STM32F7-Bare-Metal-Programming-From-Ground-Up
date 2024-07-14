/*
 * led.c
 *
 *  Created on: Nov 1, 2023
 *      Author: subra
 */

// Configuring the green(MODER0), blue(MODER7) and red(MODER14) led pins as outputs.
// Configure the GPIOB_MODE_R register. MODER0, MODER7, and MODER14 will each be set to 2'b01 to configure them as outputs.

#include "led.h"

void all_leds_init(void)
{
	// Enable clock access to port B.
	RCC->AHB1ENR |= GPIOB_CLK_EN;

	// Configure GPIOs as outputs to drive LEDs.
	GPIOB->MODER |= USER_LED1_MODER0 | USER_LED2_MODER0 | USER_LED3_MODER0;
	GPIOB->MODER &= ~(USER_LED1_MODER1 | USER_LED2_MODER1 | USER_LED3_MODER1);

}

void all_leds_on(void)
{
	GPIOB->ODR |= red_led | green_led | blue_led;
}

void all_leds_off(void)
{
	GPIOB->ODR &= ~(red_led | green_led | blue_led);
}

void all_leds_toggle(void)
{
	GPIOB->ODR ^= red_led | green_led | blue_led;
}

void led_on(ledType led)
{
	GPIOB->ODR |= led;
}

void led_off(ledType led)
{
	GPIOB->ODR &= ~led;
}

void led_toggle(ledType led)
{
	GPIOB->ODR ^= led;
}


