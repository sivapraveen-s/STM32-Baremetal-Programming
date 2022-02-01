/*
 * uart.h
 *
 *  Created on: Dec 31, 2021
 *      Author: Sivapraveen
 */

#ifndef UART_H_
#define UART_H_


#include <stdint.h>
#include "stm32f4xx.h"

void uart2_rxtx_init(void);
void uart2_tx_init(void);
char uart2_read(void);

#endif /* UART_H_ */
