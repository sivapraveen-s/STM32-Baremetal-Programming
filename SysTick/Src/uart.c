/*
 * uart.c
 *
 *  Created on: Dec 31, 2021
 *      Author: Sivapraveen
 */

/*
 * Uart:
 *
 * Universal Asynchronous Receiver Trasnmitter
 *
 * Serial Vs Parallel
 *
 * Parallel: 8 bit data is transferred the same time
 * Serial  : 8 bit data is transferred one bit at a time
 *
 * Serial data communication uses two methods
 *
 * Synchronous: Clock is transmitted with data
 * Asynchronous:No clock is transmitted. Transmitter and receiver agree on the
 *              clock speed for the data transmission (baudrate)
 *
 *
 * UART: Universal Asynchronous Receiver Transmitter
 * USART:Universal Synchronou Asynchronous Receiver Transmitter
 *
 *
 * UART Transmission Modes
 *
 * Duplex: Data can be transmitted and Received
 * Simplex: Data can be transmitted only or received only i.e one direction only
 *
 * Half Duplex:
 * Data can be transmitted in only one way at a time
 *
 * Full Duplex: Data can be transmitted in both ways at a time
 *
 * Protocol Summary: In ASYNC Transmission, each byte(character) is packed between start and stop bits
 * - Start bit is always 1 bit, the value of the start bit is always 0
 * - Stop bit can be 1 or 2 bits, the value of the stop bit is always 1
 *
 * E.g: Transmitting ASCII 'A' = 0100 0001
 *
 * One frame: 11 0100-0001 0    => 11 represents stop bit
 * 						   		=> 0100-0001 = "A"
 * 						   		=> 0 represents start bit
 * UART Configuration:
 * Baudrate: Connection Speed expressed in bits per second
 * Stop bit: Number of stop bit transmitted can be one -or- two
 * Parity: Indicate the parity mode, whether ODD -or- Even used for Error Checking
 * Mode: Specifies whether RX -or- TX mode is enabled -or- Disabled
 * Word Length: Specifies the number of data bits transmitted or received. Can be 8-bits -or- 9-bits
 * Hardware Flow Control: Specifies Whether Hardware Flow Control is enabled or disabled.
 *
 *
 *
 *
 */

/*
 * Sample - Work Flow
 * 1. Enable Clock access for UART2 here clock bus used is APB1 Bus
 * 2. Enable Clock access for GPIO, because UART Tx and Rx pin is PA2 and PA3 i.e. PORTA_PIN2 and PORTA_PIN3
 */
/*
 * Registers used:
 * RCC_AHB1ENR - GPIOAEN (bit0)th
 * RCC_APB1ENR - USART2EN (bit17)th
 *
 *
 *
 */

#include "uart.h"

#define GPIOAEN 		(1U<<0)			//	(RCC_AHB1ENR-BIT0)
#define UART2EN			(1U<<17)		//	(RCC_APB1ENR-BIT17)

#define SYS_FREQ 		16000000		// 16Mhz default
#define APB1_CLK		SYS_FREQ		//  Sys clock is taken and divide by 1, so that all the buses would take

#define UART_BAUDRATE 	115200

#define CR1_TE			(1U<<3)
#define CR1_RE 			(1U<<2)
#define CR1_UE			(1U<<13)

#define SR_TXE			(1U<<7)
#define SR_RXNE 		(1U<<5)

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}



/*
 * Both UART Tx and Rx Init
 */

void uart2_rxtx_init(void)
{
	/***************** Configure UART GPIO Pin ********************/
	/* 1. Enable Clock Access to GPIOA */
	/* 2. Set PA2 mode to Alternate Function Mode PA2 - UART2_TX Pin*/
	/* 3. Set PA2 Alternate Function type to UART_TX (AF07) */

	//1
	RCC->AHB1ENR |= GPIOAEN;

	//2
	GPIOA->MODER &= ~(1U<<4);				// Clearing BIT4 to 0
	GPIOA->MODER |= (1U<<5);				// Set BIT5 to 1

	//3
	GPIOA->AFR[0] &= ~(1U<<11);				// AFRL has Function Low and Function High Register
	GPIOA->AFR[0] |= (1U<<10); 				// in the driver, the AFR[0] = GPIOx_AFRL
	GPIOA->AFR[0] |= (1U<<9);				//				  the AFR[1] = GPIOx_AFRH
	GPIOA->AFR[0] |= (1U<<8);				// Choose function type as AF7 i.e 0111 for PA0 is for AFRL0[3:0]
											// for PA1 = AFRL1
											// for PA2 = AFRL2 (UART2_TX), so set AFRL2 @AF7


	/* [rxtx] Set PA3[UART2RX] mode to atlernate function mode */
	GPIOA->MODER &= ~(1U<<6);				// GPIOx_MODER Register BIT6
	GPIOA->MODER |= (1U<<7);				// GPIOx_MODER Register BIT7

	/* [rxtx] Set PA3 alternate function type to UART_RX [AF07] */
	// Here AFR has BIT0 to BIT3 for PIN1, BIT4 to BIT7 for PIN2
	// So, AFR[0] contains alternate function type for PIN0 to PIN7, remaining PIN8 to PIN15 will be in AFR[1]

	// Here PA3 for RX pin for USART2 so BIT12 to BIT15
	// AF07 = 0111 (BIT15 to BIT12)
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	/***************** Configure UART Module *********************/
	/* 4. Enable Clock Access to UART2 */
	/* 5. Configure Baudrate */
	/* 6. Configure the Transfer Direction */
	/* 7. Enabled UART Module */

	//4
	RCC->APB1ENR |= UART2EN;

	//5
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	//6
	USART2->CR1 = CR1_TE;		// BOTH Tx and Rx should be enable, BIT2 of USART_CR1 is RE Enable Bit
	USART2->CR1 |= CR1_RE;		// BIT3 of USART_CR1 is TE Enable Bit

	//7
	USART2->CR1 |= CR1_UE;		// Enable UE

}


/*
 * USART_READ
 *
 * Wait for the receive data register to fill it.
 * The Receive Data Register bit will be USART_SR status register of USART
 * USART_SR BIT5 - RXNE (Rx NOT Empty)
 *
 * Once the bit is set as Not empty, we can read the received data in the DATA register
 *
 *
 */

char uart2_read(void)
{
	/* Makesure the Receive data register is not empty */

	while(!(USART2->SR & SR_RXNE)) {}

	//read data from DR
	return USART2->DR;
}

/*
 * 1. For Checking Transmit data register, the USART Status Register will helps to find
 *    USART_SR BIT7 for TXE Status
 * 		TXE bit is 1 indicates, TX buffer is empty ready to load
 * 		TXE bit is 0 indicates, Not yet ready to load
 * 2. For storing data, we will use Data Register
 *    and doing AND for 8bit
 *
 *
 *
 */
void uart2_write(int ch)
{
	/* Make Sure the transmit data register is empty */
	/* Write to transmit data register */

	while(!(USART2->SR & SR_TXE)){}				// IF the bit is SET, return will be 1 or else 0, wait until the SR->TXE register is to Set then only we can able to write

	USART2->DR = (ch & 0xFF);
}


/*
 * 1. Enabling Clock Access to GPIOA by Enabling BIT0 in RCC_AHB1ENR
 * 2. For Choosing PA2(UART2_TX) as Alternate pin, needs to go to GPIOx_MODER register
 *    in that PA2 = MODER2 [BIT4 BIT5]
 *    for alternate mode selection, needs to set BIT4 of GPIOx_MODER to 0
 *                             and  needs to set BIT5 of GPIOx_MODER to 1
 * 3. Setting Alternate function type as AF7 in the register GPIOx_AFRL, we are using PA2 so
 *    choose AFRL2 for PA2 and Set as AF7 that means,
 *    AF7 - 0111 [BIT11, BIT10, BIT9, BIT8],
 *    note: GPIOx_AFR = GPIO alternate type register has totally 2 register
 *    		GPIOx_AFRL - handles all the pins from 0 to 7 and
 *    		GPIOx_AFRH - handles all the pins from 8 to 15.
 *    		in the driver both holds in array GPIOA_>AFR[0] - PIN0 to PIN7 and GPIOA->AFR[1] - PIN8 to PIN15
 *	 As per datasheet they have mention alternate function type is AF7 for setting it has 4digit bit holding
 *
 *
 *	4. for Enabling Clock Access to UART2 Module, UART2 is connected in the BUS - APB1 Bus, so we should enable
 *	   the APB1 Bus to provide clock access
 *	   RCC->APB1ENR BIT17 - UART2EN
 * 5. Configure Baudrate
 * 6. TE bit enable for Transmitter enable in USART2_CR1 control register BIT3
 *	  here in USART has three control register,
 *	  all the register has special control, all the bit setting from setting Start Bit stop bit to Parity bit
 *
 * 7. Enabling USART2 Module, we can enabole the USART2 module at
 *    the USART control register by setting BIT13 - UE Enable
 *
 *  * Work Flow
 * 1. Enable Clock access for UART2 here clock bus used is APB1 Bus
 * 2. Enable Clock access for GPIO, because UART Tx and Rx pin is PA2 and PA3 i.e. PORTA_PIN2 and PORTA_PIN3
 */

void uart2_tx_init(void)
{
	/***************** Configure UART GPIO Pin ********************/
	/* 1. Enable Clock Access to GPIOA */
	/* 2. Set PA2 mode to Alternate Function Mode PA2 - UART2_TX Pin*/
	/* 3. Set PA2 Alternate Function type to UART_TX (AF07) */

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(1U<<4);				// Clearing BIT4 to 0
	GPIOA->MODER |= (1U<<5);				// Set BIT5 to 1

	GPIOA->AFR[0] &= ~(1U<<11);				// AFRL has Function Low and Function High Register
	GPIOA->AFR[0] |= (1U<<10); 				// in the driver, the AFR[0] = GPIOx_AFRL
	GPIOA->AFR[0] |= (1U<<9);				//				  the AFR[1] = GPIOx_AFRH
	GPIOA->AFR[0] |= (1U<<8);				// Choose function type as AF7 i.e 0111 for PA0 is for AFRL0[3:0]
											// for PA1 = AFRL1
											// for PA2 = AFRL2 (UART2_TX), so set AFRL2 @AF7



	/***************** Configure UART Module *********************/
	/* 4. Enable Clock Access to UART2 */
	/* 5. Configure Baudrate */
	/* 6. Configure the Transfer Direction */
	/* 7. Enabled UART Module */

	RCC->APB1ENR |= UART2EN;

	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	USART2->CR1 = CR1_TE;		// Only Setting TE not overwriting

	USART2->CR1 |= CR1_UE;		// Enable UE




}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

