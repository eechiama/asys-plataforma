/* ========= include files =========== */
/* =================================== */
#include <Arduino.h>
#include "ap_generator.h"
#include "ap_uart.h"
#include "pr_timer2_pwm.h"

/* ======== private constants ======== */
/* =================================== */

// estado_generador
const uint8_t GENERATOR_RESET = 0;
const uint8_t GENERATOR_WAITING = 1;
const uint8_t GENERATOR_ACTIVE = 3;

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

// MDE del generador de funciones con PWM
void Generator( void ){
  static uint8_t estado_generador = GENERATOR_RESET;

  switch( estado_generador ){

    case GENERATOR_RESET:
      pwm_stop();
      estado_generador = GENERATOR_WAITING;
      break;

    case GENERATOR_WAITING:
      // casos: comandos para configurar la forma de la señal modulada en la salida de PWM
      if( command == PWM_SINE ){
        command = NO_COMMAND;
        pwm_config( SINE, rx_pwm_divider );
        pwm_start();
        estado_generador = GENERATOR_ACTIVE;
      }
      if( command == PWM_SQUARE ){
        command = NO_COMMAND;
        pwm_config( SQUARE, rx_pwm_divider );
        pwm_start();
        estado_generador = GENERATOR_ACTIVE;
      }
      if( command == PWM_RAMP ){
        command = NO_COMMAND;
        pwm_config( RAMP, rx_pwm_divider );
        pwm_start();
        estado_generador = GENERATOR_ACTIVE;
      }
      if( command == PWM_HIGH ){
        command = NO_COMMAND;
        pwm_config( LOGIC_HIGH, 1 );
        pwm_start();
        estado_generador = GENERATOR_ACTIVE;
      }
      if( command == PWM_ECG ){
        command = NO_COMMAND;
        pwm_config( ECG, rx_pwm_divider );
        pwm_start();
        estado_generador = GENERATOR_ACTIVE;
      }
      break;

    case GENERATOR_ACTIVE:
      // caso: detener el generador, apagar la salida de PWM
      if( command == PWM_OFF ){
        command = NO_COMMAND;
        pwm_stop();
        estado_generador = GENERATOR_WAITING;
        Serial.write( "0." );
      }
      break;
      
    default:
      estado_generador = GENERATOR_RESET;
      break;
  }
}
