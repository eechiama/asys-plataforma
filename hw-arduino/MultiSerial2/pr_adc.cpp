/* ========= include files =========== */
/* =================================== */
#include "pr_adc.h"
#include "dr_adc.h"
#include <TimerOne.h>

/* ======== private constants ======== */
/* =================================== */

/* ======== private datatypes ======== */
/* =================================== */

/* ==== private global variables ===== */
/* =================================== */

/* ==== shared global variables ====== */
/* =================================== */

/* ======= private prototypes ======== */
/* =================================== */

/* ======= private functions ========= */
/* =================================== */

/* ======== public functions ========= */
/* =================================== */

// Función para leer una muestra del adc y colocarla en *value.
// @return false si no había ninguna muestra lista del adc.
bool adc_read( uint16_t *value ){
  if ( f_sample_ready ) {
    f_sample_ready = 0;
    *value = adc_sample;
    return true;  
  }
  return false;
}

// Función para ajustar la frecuencia de muestreo.
void adc_sampleRate(uint16_t s_rate){
  double microseg = (double)1/(double)1000000;
  double Ts=0;
  uint32_t cantidad_microsegundos=0;

  Ts = (double)1 / (double)s_rate ;

  cantidad_microsegundos = (uint32_t) ( Ts / microseg ); 

  timer1_period(cantidad_microsegundos);
}

void Start_Sampling(){
  Timer1.start();
}

void Stop_Sampling(){
  Timer1.stop();
}
