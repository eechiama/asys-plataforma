#include "dr_timer2_pwm.h"

const byte PIN_OC2A = 11;     // PWM PIN

const uint8_t NO_DATA = 0;    // LUT init size

/* ==== private global variables ===== */
/* =================================== */

static const uint8_t *LUT = NULL;

static uint16_t LUT_size = NO_DATA;

static volatile uint16_t LUT_inx = 0;

// para dividir la frecuencia
static volatile uint16_t count = 1;

static uint16_t freqDivider = 1;

/* ======= private functions ========= */
/* =================================== */

ISR (TIMER2_OVF_vect) {
  
  if( count == freqDivider ){
    OCR2A = *(LUT + LUT_inx);
    LUT_inx++;
    if( LUT_inx == LUT_size ) LUT_inx = 0;
    count = 1;
  }
  else{
    count++;
  }
}

/* ======== public functions ========= */
/* =================================== */

void timer2_pwm_init( void ){

  pinMode( PIN_OC2A , OUTPUT);

  // Set Fast PWM mode with non-inverting mode on OC2A pin
  TCCR2A = bit( COM2A1 ) | bit( WGM21 ) | bit( WGM20 );
  TCCR2B = 0x0;

  // clear the interrupt register, in case of any arduino default setting.
  TIMSK2 = 0x0;
  
  timer2_pwm_duty(0);
  timer2_reset_counter();
}

void timer2_pwm_duty( uint8_t val ){
  OCR2A = val; 
}

/* enable/disable the timer2 overflow interrupt
 * (where typically I update the duty cycle)
 * use cases:
 *  disable: when outputting the logic value HIGH the duty cycle is always the same (0xFF, 100%)
 *           so it doesn't need to be updated.
*/
void timer2_overflow_interrupt( bool action ){
  if( action == true ){
    TIMSK2 |= bit( TOIE2 );
  }
  if( action == false ){
    TIMSK2 &= ~bit( TOIE2 );
  }
}

void timer2_reset_counter( void ){
  TCNT2 = 0x0;  
}

void timer2_set_prescaler( void ){
  // Set prescaler = 1; (setting prescaler != 0 also starts the timer!)
  TCCR2B = bit( CS20 );
}

void timer2_clear_prescaler( void ){
  // Clear the prescarler: no clock source (timer stopped)
  TCCR2B &= ~bit( CS20 );
}

// load the look up table, reset it's index and setup the frequency divider
// also resetting the ISR counter (used to 'divide' the frequency)
void LUT_load(const uint8_t *data, uint16_t qtyBytes, uint16_t divider){
  LUT =  &(*data);
  LUT_size = qtyBytes;
  freqDivider = divider;
  count = 1;
}

void LUT_restart( void ){
  LUT_inx = 1;
}
