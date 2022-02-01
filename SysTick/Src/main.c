/*
 * Common for ALL
 * 1. Set the Clock access for the GPIO
 * 2. MODER configuration for GPIO
 *
 *
 */

#if 1
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOAEN				(1U<<0)
#define PIN5				(1U<<5)

#define LED_PIN				PIN5

uint32_t sensorValue;


int main()
{

	/* Enable Clock Access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA5(led pin) as Output pin */
	GPIOA->MODER |= (1U<<10);				// Setting GPIOA PIN5 as OUTPUT so In MODER register BIT 10 and 11
											// to be used to set, here output so 11 bit as 0 and 10 bit as 1
	GPIOA->MODER &= ~(1U<<11);


	uart2_tx_init();
	pa1_adc_init();
	start_conversion();

	while(1)
	{
		sensorValue = adc_read();
		printf("%s> Sensor Value: %d/%u \n\r", __FUNCTION__,
											   sensorValue,
											   sensorValue);

		//Excuting LED every one second with Systick delay

		GPIOA->ODR ^= LED_PIN;
		systickDelayMs(1000);		// 1000ms
	}
}


#endif



