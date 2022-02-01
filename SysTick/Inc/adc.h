/*
 * adc.h
 *
 *  Created on: 13-Jan-2022
 *      Author: hp
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);


#endif /* ADC_H_ */
