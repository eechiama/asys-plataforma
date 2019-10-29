#ifndef PR_TIMER2_PWM_H
#define PR_TIMER2_PWM_H
/* ===== include files ===== */
/* ========================= */
#include <Arduino.h>

/* ======= constants ======= */
/* ========================= */

// indicadores de señales para pwm_config()
const uint8_t NO_SIGNAL = 10;
const uint8_t SINE = 11;
const uint8_t RAMP = 12;
const uint8_t LOGIC_HIGH = 13;
const uint8_t SQUARE = 14;
const uint8_t ECG = 15;
const uint8_t IMPULSE = 16;

// Divisores de frecuencia para las señales
// estos divisores son comunes tanto para el seno de 1kHz como para el de 500Hz
const uint8_t DIV_2 = 2;    // 500 Hz
const uint8_t DIV_4 = 4;    // 250 Hz
const uint8_t DIV_5 = 5;    // 200 Hz
const uint8_t DIV_10 = 10;  // 100
const uint8_t DIV_20 = 20;  // 50
const uint8_t DIV_25 = 25;  // 40
const uint8_t DIV_50 = 50;  // 20

/* ======= datatypes ======= */
/* ========================= */

/* === public variables ==== */
/* ========================= */

/* === public functions ==== */
/* ========================= */
void pwm_config( uint8_t inx, uint16_t divider );
void pwm_start( void );
void pwm_stop( void );

#endif /* PR_TIMER2_PWM_H */
