#ifndef DR_TIMER2_PWM_H
#define DR_TIMER2_PWM_H

/* ===== include files ===== */
/* ========================= */
#include <Arduino.h>

/* ======= constants ======= */
/* ========================= */
const uint8_t MAX_DUTY = 0xFF;
const uint8_t HALF_DUTY = 127;

/* ======= datatypes ======= */
/* ========================= */

/* === public variables ==== */
/* ========================= */

/* === public functions ==== */
/* ========================= */
void timer2_pwm_init( void );
void timer2_pwm_duty( uint8_t val );

void timer2_overflow_interrupt( bool action );
void timer2_reset_counter( void );

// timer2 ON/OFF depende de un prescaler != 0
void timer2_set_prescaler( void );
void timer2_clear_prescaler( void );

void LUT_load( const uint8_t *data, uint16_t qtyBytes, uint16_t divider );
void LUT_restart( void );

#endif /* DR_TIMER2_PWM_H */
