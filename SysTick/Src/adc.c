/*
 * ADC - Analog to Digital Converter
 *
 * Physical quantity is converted to the electrical signals using the device called "Transducer"
 *
 * Transducer converts physical either voltage or current, Transducer used to generate electrical outputs
 * are refered to sensors
 *
 *
 *	 	n-bit			|	number of steps		|	Step Size
 * 8-bit 				| 			256			|	5v/256 = 19.53 mV
 * 10-bit				| 			1024		|	5v/1024	= 4.88 mV
 * 12-bit				|			4096		|	5v/4096	= 1.2 mV
 * 16-bit 				|			65,536		|	5v/65536 = 0.076 mV
 *
 * Taking Vref - 5V
 *
 *
 *
 * ************************
 * ADC Independent Modes
 * ************************
 * 1) Single Channel, Single Conversion mode
 * 2) Multi Channel, Single Conversion mode
 * 3) Single Channel, Continuous conversion mode
 * 4) Multi Channel, Continuous Conversion mode
 * 5) Injected continuous Conversion Mode
 *
 *
 * 1) Single Channel, Single Conversion mode
 * 			- Simple ADC Mode
 * 			- ADC performs a single conversion of a single channel X and stops after conversion is complete
 *
 * 			Example: Measurement of voltage level of determine if a system should be started or not
 *
 * 			WorkFlow: start ---> CHX ---> Stop
 *
 * 2) Multi Channel, Single Conversion Mode
 * 			- Used to convert multiple channels successively
 * 			- Upto 16 different channels with different sampling times can be converted on the stm32f4
 *
 * 			Example: Measurement of multiple sensors to determine whether a system should start -or- not
 *
 * 			WorkFlow: start ---> CHX ---> CHn ---> stop
 * 3) Single Channel, continous conversion mode
 *   		- Used to convert a single channel continuously
 *   		- Works in the background without intervention from the CPU
 *
 *   		Example: measurement of room temperaute continously to adjust air conditioner
 *
 * 4) Multi Channel Continouse Conversion mod
 *			- Used to convert multiple channel continuously
 *			- Up to 16 different channels with different sampling times can be converted on the stm32f4
 *
 *			Example: continously measure the multiple accelerometer to adjust robotic arms
 *
 * 5) Injected conversion mode
 * 			- Intended for use when the conversion is triggered by an external event or by software.
 * 			- the injected group has priority over the regular channel group
 * 			- interrupts the conversion of the current channel in the regular channel group
 *
 * 			laymen term: For say, the ADC1 conversion going on from CH0 - CH1 - CHn
 * 			             inbetween suddenky the injected converted is triggered by external or by software
 * 			             then suddenly the injected conversion channel(CHn) will be excuted untill the normal
 * 			             conversion holds and once the injected conversion finished the work then the normal
 * 			             excuteion begins where it stopped
 * 			             Note: here group is a set of channel grouped together
 * 			Example: for sync. the conversion of channels to an event.
 *
 *
 *
 * Bus
 *  RCC_APB2ENR - ADC1 is connected with the APB2 Bus, BIT8 is the ADC1EN bit
 *
 *
 *
 *  Registers USED
 *  RCC_APB2ENR - BIT8 (ADC1 EN)
 *  RCC_AHB1ENR - BIT0 (GPIOA_EN)
 *  MODER - BIT2 & BIT3 (if you are working with PA1 Pin)
 *          setting to analog mode
 *  ADC_SQR3 - Configuring the n channel sequence's
 *  ADC_SQ3, ADC_SQR2 and ADC_SQ1 - if configuring more than 1 channels
 *  ADC_SQ1 - BIT20 to BIT23 (for setting Sequence Length)
 *
 *
 *
 * _______________________________________________________________________
 * ADC Configure with 3 Channels
 * Example - 1
 * suppose we need configure 3 channels namely CH2, CH3 and CH5
 * in the format for
 *      first = CH5
 *      second = CH2
 *      third = ch3
 * for configuring we need to use ADC_SQR3 Register
 * in the register series will follow SQ1 to SQ6 in the ADC_SQR3 and
 * SQ7 to SQ12 @ADC_SQR2 and SQ12 to SQ16 @ADC_SQR1 register respectively
 *
 * SQ1[4:0] - Sequence #1
 * SQ2[4:0] - Sequence #2 so on.
 * [4:0] represents, it contains 5 bits
 *
 *
 * for say if we need to run the CH5 first and CH2 to second and CH3 to third
 * we need to set SQ1 as CH5 that means we need set binary #5 at the place SQ1 @ADC_SQR3
 * and Set binary 2 for CH2 at SQ2 @ADC_SQR3 and set Channel 3 in binary format ibn SQ3[4:0] @ADC_SQR3
 *
 * @ADC_SQR3 registe
 * SQ1[4:0] - 0b 0101     (setting as CH5 for executing 1st in sequence -or- seqeunce at start)
 * SQ2[4:0] - 0b 0010	  (setting as CH2)
 * SQ3[4:0] - 0b 0011 	  (setting as CH3)
 *
 * Then set the Sequence length @ADC_SQ1 register BIT20 to BIT23
 * ADC_SQ1[3:0] (BIT20 to BIT23)
 * 0000 - 1 Conversion
 * 0001 - 2 Conversion
 * 1111 - 16 Conversion
 *
 *________________________________________________________________________
 *
 *
 * #Workflow:
 * 1. Init adc
 * 	  1.1 Enable Clock access to GPIOx Pin depends on which GPIO pins are used
 * 	  1.2 Set the mode, eg for PA1 pin, need to set a analog mode @MODER register
 * 	  1.3 Configure clock access to ADC
 * 	  1.4 Configure Sequence start and number of sequence depends on the number of channels
 * 	  1.5 Configure Conversion Sequence length
 * 	  1.6 Enable ADC Module
 * 2. Start Conversion
 *    2.1 Select Continous Conversion if needed, it like running in while loop, it keeps on converting the
 *        adc or else it will do the coversion only once
 * 	  2.2 Start the conversion with timer -or- software start
 * 3. ADC Read
 *    3.1 Wait for Conversion to be completed, so monitor the status bit ADC_EOC bit @ADC_SR register
 *        EOC = @ADC_SR BIT1
 *    3.2 one the conversion is upon completed, return the Data Register there we will get the values
 *    	  ADC1->DR
 *
 * There are two main register available, for control register and status register
 * for turning on ADC module or timer module etc we need to use control register
 * for checking the read status, uart rx wait status etc will be read from Status register
 *
 *
 */

#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN					(1U<<0)
#define ADC1EN					(1U<<8)
#define ADC_CH1					(1U<<0)
#define ADC_SEQ_LEN_1			0x00
#define CR2_ADON				(1U<<0)
#define CR2_SWSTART				(1U<<30)
#define SR_EOC 					(1U<<1)
#define CR2_CONT				(1U<<1)

void pa1_adc_init(void)
{
	/*** Configure the ADC GPIO Pin ***/
	/* Enabling CLOCK access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set the mode of PA1 to analog */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/* Configure the ADC Module */
	/* Enable Clock access to ADC */
	RCC->APB2ENR |= ADC1EN;

	/*** Configure ADC Parameters ***/
	/* Conversion sequence start */
	ADC1->SQR3 = ADC_CH1;				// here setting to zero, because we are configuring only one channels
										//

	/* Conversion sequence length */
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	/* Enable ADC module */
	//For enabling adc module we need to turn on the ADC on bit from the ADC Control register here, ADC_CR2 BIT0
	ADC1->CR2 |= CR2_ADON;

}

void start_conversion(void)
{
	/* Enable Continuous Conversion */
	ADC1->CR2 |= CR2_CONT;

	/* Start adc conversion */
	// ADC SWSTART bit is in ADC_CR2 i.e ADC Control register, we can also start with timer here
	// we are starts conversin with Software Start(SWSTART)
	// ADC SWSTART @ADC_CR2 BIT30

	ADC1->CR2 |= CR2_SWSTART;


}

uint32_t adc_read(void)
{
	/* Wait For Conversion To Be Complete */
	while(!(ADC1->SR & SR_EOC)){}

	/* Read converted result */
	return (ADC1->DR);
}
