#include "dr_adc.h"
#include <TimerOne.h>

const byte adcPin = 0;                      // Pin de entrada del ADC: A0

const int PERIOD_DEFAULT = 400;             // microsegundos, para fs = 2500Hz

/* ==== private global variables ===== */
/* =================================== */
volatile uint8_t f_sample_ready = 0;

volatile uint16_t adc_sample = 0;

/* ======= private prototypes ======== */
/* =================================== */

void ADC_Convert_Start(void);

/* ======= private functions ========= */
/* =================================== */

ISR (ADC_vect) {

  // leo el resultado
  uint16_t adcReading = ADC;
  
  adc_sample = adcReading;
  f_sample_ready = 1;
}

/* ======== public functions ========= */
/* =================================== */

void adc_init(void){

  // ADC Setup
  ADMUX =   bit (REFS0) | (adcPin & 0x07);
  
  // peripheral on  
  ADCSRA =  bit (ADEN);
  
  // clear prescaler bits 
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2));
  
  // prescaler en 128. ADC Clock Freq 125kHz.
  // 1 conversión lleva 13 ciclos de adc clock.
  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);

  // habilito las interrupciones.   
  ADCSRA |= bit(ADIE);
}

void ADC_Convert_Start(void){
  // Empiezo una conversión.
  ADCSRA |= bit (ADSC);
}

void timer1_init(){
  Timer1.initialize(PERIOD_DEFAULT);
  Timer1.attachInterrupt(ADC_Convert_Start);  
}

// Para cambiar el período del timer (osea, la freq de muestreo)
void timer1_period(uint32_t microsegs){
  Timer1.stop();
  Timer1.initialize(microsegs);
}
