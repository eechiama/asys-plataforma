#ifndef PR_ADC_H
#define PR_ADC_H

#include <Arduino.h>

bool adc_read( uint16_t *value );

void adc_sampleRate(uint16_t s_rate);

void Start_Sampling();

void Stop_Sampling();

#endif /* PR_ADC_H */
