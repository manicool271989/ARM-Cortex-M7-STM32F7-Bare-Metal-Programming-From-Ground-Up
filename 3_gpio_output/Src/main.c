#include "stm32f7xx.h"

#define GPIOB_CLK_EN	(1U<<1) // Shifting 1 to postion 1. Example: (1U<<5) 0000 0000 -> 0001 0000

// Configuring the green(MODER0), blue(MODER7) and red(MODER14) led pins as outputs.
// Configure the GPIOB_MODE_R register. MODER0, MODER7, and MODER14 will each be set to 2'b01 to configure them as outputs.

#define USER_LED1_MODER	(1U<<0)  // Set bit 0 to 1.
#define USER_LED2_MODER	(1U<<14) // Set bit 14 to 1.
#define USER_LED3_MODER	(1U<<28) // Set bit 28 to 1.

#define USER_LED1 (1U<<0)  // green led
#define USER_LED2 (1U<<7)  // blue led
#define USER_LED3 (1U<<14) // red led

int main()
{
	/* Enable clock access to port B. */

	//RCC_AHB1EN_R |= GPIOB_CLK_EN;  // |= operation is bitwise OR operation and will only set the bit that is defined by GPIOB_CLK_EN. Leaves all other bits alone. This is known as Friendly Programming.
	RCC->AHB1ENR |= GPIOB_CLK_EN;

	/* Configure led pins as output pins. */

	//GPIOB_MODE_R |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;
	GPIOB->MODER |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

	while(1)
	{
		/* Turn on all leds. */

		//GPIOB_OD_R |= USER_LED1 | USER_LED2 | USER_LED3;

		/* Experiment 2: toggle */

		/* Line below is old way of setting ODR register */
		//GPIOB_OD_R ^= USER_LED1 | USER_LED2 | USER_LED3;  // Bitwise XOR (^=) can be used to toggle pins.
		/* Line below is new way of setting ODR register using struct members */
		GPIOB->ODR ^= USER_LED1 | USER_LED2 | USER_LED3;
		for(int i = 0; i < 1000000; i++)
		{
		}

	}
}
