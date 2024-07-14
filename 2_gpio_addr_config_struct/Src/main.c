// Where is the LED connected?
// -Pin ? green led = 0 | blue led = 7 | red led = 14
// -Port ? green led = B | blue led = B | red led = B

#include <stdint.h>

#define PERIPH_BASE 	0x40000000UL // Type Unsigned Long
#define AHB1_OFFSET 	0x20000UL
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1_OFFSET)
#define GPIOB_OFFSET 	0x400UL
#define GPIOB_BASE 		(AHB1PERIPH_BASE + GPIOB_OFFSET)

#define RCC_OFFSET 		0x3800UL
#define RCC_BASE 		(AHB1PERIPH_BASE + RCC_OFFSET)

// Below two lines are no longer needed as we define the register through struct implementation.
//#define AHB1EN_R_OFFSET 0x30UL

//#define RCC_AHB1EN_R 	(*(volatile unsigned int *) (RCC_BASE + AHB1EN_R_OFFSET))  // Type-cast as uint pointer and then dereference to make this a register.

// Below two lines are no longer needed as we define the MODE register through struct implementation.
//#define MODER_OFFSET 	0x0000UL
//#define GPIOB_MODE_R	(*(volatile unsigned int *) (GPIOB_BASE + MODER_OFFSET))

// Below two lines are no longer needed as we define the ODR register through struct implementation.
//#define ODR_OFFSET		0x14UL
//#define GPIOB_OD_R		(*(volatile unsigned int *) (GPIOB_BASE + ODR_OFFSET))




#define GPIOB_CLK_EN	(1U<<1) // Shifting 1 to postion 1. Example: (1U<<5) 0000 0000 -> 0001 0000

// Configuring the green(MODER0), blue(MODER7) and red(MODER14) led pins as outputs.
// Configure the GPIOB_MODE_R register. MODER0, MODER7, and MODER14 will each be set to 2'b01 to configure them as outputs.

#define USER_LED1_MODER	(1U<<0)  // Set bit 0 to 1.
#define USER_LED2_MODER	(1U<<14) // Set bit 14 to 1.
#define USER_LED3_MODER	(1U<<28) // Set bit 28 to 1.

#define USER_LED1 (1U<<0)  // green led
#define USER_LED2 (1U<<7)  // blue led
#define USER_LED3 (1U<<14) // red led


#define __IO	volatile

typedef struct
{
	uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR;
} RCC_TypeDef;

typedef struct
{
	__IO uint32_t MODER;
	uint32_t DUMMY[4];
	__IO uint32_t ODR;
} GPIO_TypeDef;

#define GPIOB ((GPIO_TypeDef*) GPIOB_BASE)
#define RCC ((RCC_TypeDef*) RCC_BASE)


int main(void)
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

