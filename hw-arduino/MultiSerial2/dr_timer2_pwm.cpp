/* ========= include files =========== */
/* =================================== */
#include <Arduino.h>
#include "dr_timer2_pwm.h"

/* ======== private constants ======== */
/* =================================== */
const byte MAX_8BIT = 0xFF;

/* ======== private datatypes ======== */
/* =================================== */

/* ==== private global variables ===== */
/* =================================== */

// inx to waveform table
volatile uint8_t inx_wfm = 0;

/* ==== shared global variables ====== */
/* =================================== */

volatile uint8_t table_mod_wfm[ MAX_8BIT + 1 ] = { 0 };

/* ======= private prototypes ======== */
/* =================================== */

/* ======= private functions ========= */
/* =================================== */

// event: timer overflow
ISR (TIMER2_OVF_vect) {
  // flags are cleared by hardware 
  // update the duty cycle
  inx_wfm++;
  OCR2A = table_mod_wfm[ inx_wfm ];
  inx_wfm %= MAX_8BIT;
}

/* ======== public functions ========= */
/* =================================== */

void timer2_pwm_init( void ){

  pinMode( pin oc2a ? , OUTPUT);

  // Set Fast PWM mode with non-inverting mode on OC2A pin
  TCCR2A = bit( COM2A1 ) | bit( WGM21 ) | bit( WGM20 );
  
  // enable timer overflow interrupt
  TIMSK2 = bit( TOIE2 );

  // duty cycle = 0
  OCR2A = 0;
}

void timer2_start( void ){
  // reset the timer counter
  TCNT2 = 0x0;

  // reset the inx to the modulated waveform table
  inx_wfm = 0;
  
  // Set prescaler = 1; (setting prescaler != 0 also starts the timer!)
  TCCR2B = bit( CS20 );
}

void timer2_stop( void ){
  // Clear the prescarler: no clock source (timer stopped)
  TCCR2B &= ~bit( CS20 );
}
