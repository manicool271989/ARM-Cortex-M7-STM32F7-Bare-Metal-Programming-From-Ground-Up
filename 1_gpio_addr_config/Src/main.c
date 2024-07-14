// Where is the LED connected?
// -Pin ? green led = 0 | blue led = 7 | red led = 14
// -Port ? green led = B | blue led = B | red led = B

#define PERIPH_BASE 	0x40000000UL // Type Unsigned Long
#define AHB1_OFFSET 	0x20000UL
#define AHB1PERIPH_BASE PERIPH_BASE + AHB1_OFFSET
#define GPIOB_OFFSET 	0x400UL
#define GPIOB_BASE 		AHB1PERIPH_BASE + GPIOB_OFFSET

#define RCC_OFFSET 		0x3800UL
#define RCC_BASE 		AHB1PERIPH_BASE + RCC_OFFSET
#define AHB1EN_R_OFFSET 0x30UL

#define RCC_AHB1EN_R 	(*(volatile unsigned int *) (RCC_BASE + AHB1EN_R_OFFSET))  // Type-cast as uint pointer and then dereference to make this a register.

#define MODER_OFFSET 	0x0000UL
#define GPIOB_MODE_R	(*(volatile unsigned int *) (GPIOB_BASE + MODER_OFFSET))

#define ODR_OFFSET		0x14UL
#define GPIOB_OD_R		(*(volatile unsigned int *) (GPIOB_BASE + ODR_OFFSET))




#define GPIOB_CLK_EN	(1U<<1) // Shifting 1 to postion 1. Example: (1U<<5) 0000 0000 -> 0001 0000

// Configuring the green(MODER0), blue(MODER7) and red(MODER14) led pins as outputs.
// Configure the GPIOB_MODE_R register. MODER0, MODER7, and MODER14 will each be set to 2'b01 to configure them as outputs.

#define USER_LED1_MODER	(1U<<0)  // Set bit 0 to 1.
#define USER_LED2_MODER	(1U<<14) // Set bit 14 to 1.
#define USER_LED3_MODER	(1U<<28) // Set bit 28 to 1.

#define USER_LED1 (1U<<0)  // green led
#define USER_LED2 (1U<<7)  // blue led
#define USER_LED3 (1U<<14) // red led


int main(void)
{
	/* Enable clock access to port B. */

	RCC_AHB1EN_R |= GPIOB_CLK_EN;  // |= operation is bitwise OR operation and will only set the bit that is defined by GPIOB_CLK_EN. Leaves all other bits alone. This is known as Friendly Programming.

	/* Configure led pins as output pins. */

	GPIOB_MODE_R |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

	while(1)
	{
		/* Turn on all leds. */

		//GPIOB_OD_R |= USER_LED1 | USER_LED2 | USER_LED3;

		/* Experiment 2: toggle */

		GPIOB_OD_R ^= USER_LED1 | USER_LED2 | USER_LED3;  // Bitwise XOR (^=) can be used to toggle pins.
		for(int i = 0; i < 1000000; i++)
		{
		}

	}
}

