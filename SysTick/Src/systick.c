/*
 * For Systick the details of this will not be available at stm32 documentation
 * because this systick is used in all the cortex M4 in ARM Processor. eg: in TI, STM32 and all the MCU which uses arm will have Systick
 *
 * We can use get the documentation details from Cortex-m4 generic user guide provided by arm
 *
 *	For all the ARM Processor we can use this Systick library
 *
 */

#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL			16000			// 1m sec
#define CTRL_ENABLE					(1U<<0)			// Systick Enable
#define CTRL_CLKSRC					(1U<<2)			// Processor Clock
#define CTRL_COUNTFLAG				(1U<<16)		// Count Flag

void systickDelayMs(int delay)
{
	/* Configure Systick */
	/* Reload with number of clocks per millisecond*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* Clear Systick current value register */
	SysTick->VAL = 0;

	/* Enable Systick and select internal clock source */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int indx = 0; indx < delay; indx ++)
	{
		/* wait until the COUNTFLAG is set */

		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}
	}
	SysTick->CTRL = 0;
}
