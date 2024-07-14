#include <stdio.h>
#include "uart.h"
#include "adc.h"

int main(void)
{
	uart3_tx_init();
	pa4_adc_init();

	while(1)
	{
		printf("%d \n\r", adc_get_data());
	}
}
