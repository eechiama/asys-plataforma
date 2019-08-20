#ifndef ADC_H
#define ADC_H

/* ===== include files ===== */
/* ========================= */
#include <Arduino.h>

/* ======= constants ======= */
/* ========================= */

/* ======= datatypes ======= */
/* ========================= */

/* === public variables ==== */
/* ========================= */
extern volatile uint8_t f_sample_ready;
extern volatile uint16_t adc_sample;

/* === public functions ==== */
/* ========================= */
void adc_init(void);
void ADC_Convert_Start(void);
void timer1_init();
void timer1_period(uint32_t microsegs);

#endif /* ADC_H */
