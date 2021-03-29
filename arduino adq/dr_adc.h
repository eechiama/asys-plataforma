#ifndef ADC_H
#define ADC_H

#include <Arduino.h>


extern volatile uint8_t f_sample_ready;

extern volatile uint16_t adc_sample;


void adc_init(void);

void ADC_Convert_Start(void);

void timer1_init();

void timer1_period(uint32_t microsegs);

#endif /* ADC_H */
