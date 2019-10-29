/* ========= include files =========== */
/* =================================== */
#include "pr_timer2_pwm.h"
#include "dr_timer2_pwm.h"

/* ======== private constants ======== */
/* =================================== */
const uint8_t SINE_SIZE = 125;
const uint16_t RAMP_SIZE = 256;
const uint8_t SQUARE_SIZE = 125;
const uint8_t IMPULSE_SIZE = 125;
const uint8_t ECG2_SIZE = 85;

/* ======== private datatypes ======== */
/* =================================== */

// LUT senoidal, 125 puntos
const uint8_t sine_wave[ SINE_SIZE ] = {
128,134,140,147,153,159,166,172,178,184,
189,195,200,206,211,215,220,224,228,232,
236,239,242,245,247,249,251,252,254,254,
255,255,255,254,254,252,251,249,247,245,
242,239,236,232,228,224,220,215,211,206,
200,195,190,184,178,172,166,160,153,147,
141,134,128,121,115,108,102,96,90,83,
77,72,66,60,55,50,45,40,35,31,
27,23,19,16,13,10,8,6,4,3,
2,1,0,0,0,1,1,3,4,6,
8,10,13,16,19,23,26,31,35,39,
44,49,54,60,65,71,77,83,89,95,
102,108,114,121,127};

// LUT de la cuadrada, 125 puntos
const uint8_t square_wave[ SQUARE_SIZE ] = {
255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,
255,255,255,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0 };

// LUT rampa, 256 puntos
const uint8_t ramp_wave[ RAMP_SIZE ] = {
0,1,2,3,4,5,6,7,8,9,
10,11,12,13,14,15,16,17,18,19,
20,21,22,23,24,25,26,27,28,29,
30,31,32,33,34,35,36,37,38,39,
40,41,42,43,44,45,46,47,48,49,
50,51,52,53,54,55,56,57,58,59,
60,61,62,63,64,65,66,67,68,69,
70,71,72,73,74,75,76,77,78,79,
80,81,82,83,84,85,86,87,88,89,
90,91,92,93,94,95,96,97,98,99,
100,101,102,103,104,105,106,107,108,109,
110,111,112,113,114,115,116,117,118,119,
120,121,122,123,124,125,126,127,128,129,
130,131,132,133,134,135,136,137,138,139,
140,141,142,143,144,145,146,147,148,149,
150,151,152,153,154,155,156,157,158,159,
160,161,162,163,164,165,166,167,168,169,
170,171,172,173,174,175,176,177,178,179,
180,181,182,183,184,185,186,187,188,189,
190,191,192,193,194,195,196,197,198,199,
200,201,202,203,204,205,206,207,208,209,
210,211,212,213,214,215,216,217,218,219,
220,221,222,223,224,225,226,227,228,229,
230,231,232,233,234,235,236,237,238,239,
240,241,242,243,244,245,246,247,248,249,
250,251,252,253,254,255 };

// LUT del impulso, 125 puntos
const uint8_t impulse_wave[ IMPULSE_SIZE ] = {
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,255,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0 };

const uint8_t ecg2[ ECG2_SIZE ] = {
94, 95, 128, 158, 187, 215, 245, 233,
202, 174, 144, 114,  94,  84,  77,  69,
72,  81,  85,  94,  93,  94,  92,  92,
92, 101, 110, 115, 123, 123, 129, 128,
127, 126, 118, 113, 107, 101,  94,  90,
91,  92,  90,  93,  92,  91,  91,  94,
95,  96,  98,  93,  94,  94,  93,  91,
93,  91,  91,  91,  94,  90,  91,  90,
92,  90,  94,  91,  90,  91,  99, 104,
114, 114, 114, 112, 108, 100,  94,  94,
93,  90,  90,  94,  94  };


/* ==== private global variables ===== */
/* =================================== */

/* ==== shared global variables ====== */
/* =================================== */

/* ======= private prototypes ======== */
/* =================================== */

void pwm_config( uint8_t inx, uint16_t divider ){
  
  if( (divider < 0) || (divider > 999) ) divider = 1;
  
  switch( inx ){
    case SINE:
      LUT_load(sine_wave, SINE_SIZE, divider );
      timer2_overflow_interrupt( true );
      timer2_pwm_duty( sine_wave[0] );      
      break;
    case SQUARE:
      LUT_load(square_wave, SQUARE_SIZE, divider );
      timer2_overflow_interrupt( true );
      timer2_pwm_duty( square_wave[0] );
      break;
    case RAMP:
      LUT_load(ramp_wave, RAMP_SIZE, divider );
      timer2_overflow_interrupt( true );
      timer2_pwm_duty( ramp_wave[0] );
      break;
    case LOGIC_HIGH:
      timer2_overflow_interrupt( false );
      timer2_pwm_duty(MAX_DUTY);
      break;
    case IMPULSE:
      LUT_load(impulse_wave, IMPULSE_SIZE, divider );
      timer2_overflow_interrupt( true );
      timer2_pwm_duty( impulse_wave[0] );      
      break;
    case ECG:
      LUT_load(ecg2, ECG2_SIZE, divider );
      timer2_overflow_interrupt( true );
      timer2_pwm_duty( ecg2[0] );
      break; 
    default:
      break;
  }
}

void pwm_start( void ){ 
  LUT_restart();
  timer2_reset_counter();
  timer2_set_prescaler();
}

void pwm_stop( void ){
  timer2_clear_prescaler();
}
