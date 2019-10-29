/* ========= include files =========== */
/* =================================== */
#include <Arduino.h>
#include "ap_buttons.h"
#include "ap_uart.h"
#include "dr_buttons.h"

/* ======== private constants ======== */
/* =================================== */

// on_sequence_step
const int SEQUENCE_ON_PWM = 1;
const int SEQUENCE_ON_SAMPLE_RATE = 2;
const int SEQUENCE_ON_ADC = 3;
const int SEQUENCE_ON = 4;

// off_sequence_step
const int SEQUENCE_OFF_ADC = 10;
const int SEQUENCE_OFF_SAMPLE_RATE = 11;
const int SEQUENCE_OFF_PWM = 12;
const int SEQUENCE_OFF = 13;

// sequence on-going indicator (sequence_status)
const int SEQUENCE_BUSY = 20;
const int SEQUENCE_NOT_BUSY = 21;

/* ======== private datatypes ======== */
/* =================================== */

/* ==== private global variables ===== */
/* =================================== */
volatile uint8_t sequence_status = SEQUENCE_NOT_BUSY;

/* ==== shared global variables ====== */
/* =================================== */

/* ======= private prototypes ======== */
/* =================================== */
void button_sequence( void );

/* ======= private functions ========= */
/* =================================== */
void button_sequence( void ){

  static uint8_t on_sequence_step = SEQUENCE_ON_PWM;
  static uint8_t off_sequence_step = SEQUENCE_OFF;

  if( sequence_enabled ){
  
    switch( on_sequence_step ){
      
      case SEQUENCE_ON_PWM:
        command = waveform_commands[inx_waveform_command];
        on_sequence_step = SEQUENCE_ON_SAMPLE_RATE;
        off_sequence_step = SEQUENCE_OFF_PWM;
        break;
  
      case SEQUENCE_ON_SAMPLE_RATE:
        command = CONFIG_SR;
        rx_fmuestreo = 2500;
        on_sequence_step = SEQUENCE_ON_ADC;
        break;
  
      case SEQUENCE_ON_ADC:
        command = START_ADC;
        on_sequence_step = SEQUENCE_ON;
        off_sequence_step = SEQUENCE_OFF_ADC;
        break;
  
      case SEQUENCE_ON:
        break;
    }
  }
  else{
  
    switch( off_sequence_step ){
      case SEQUENCE_OFF_ADC:
        command = STOP_ADC;
        off_sequence_step = SEQUENCE_OFF_PWM;
        on_sequence_step = SEQUENCE_ON_ADC;
        break;
  
      case SEQUENCE_OFF_PWM:
        command = PWM_OFF;
        off_sequence_step = SEQUENCE_OFF;
        on_sequence_step = SEQUENCE_ON_PWM;
        break;
  
      case SEQUENCE_OFF:
        sequence_status = SEQUENCE_NOT_BUSY;
        break;
    }
    
  }

}

/* ======== public functions ========= */
/* =================================== */

// MDE del modo botones
void Buttons( uint8_t *inform_status ){
  
  static uint8_t estado_buttonSM = BUTTONS_INACTIVE;
  static uint8_t queued_command = NO_COMMAND;

  switch( estado_buttonSM ){

    case BUTTONS_INACTIVE:

      if( command == START_BUTTONS ){
        command = NO_COMMAND;
        estado_buttonSM = BUTTONS_ACTIVE;
        sequence_status = SEQUENCE_BUSY;
        buttons_init();
      }
      break;

    case BUTTONS_ACTIVE:

      if( command == STOP_BUTTONS ) queued_command = STOP_BUTTONS;
      
      debounce();
      led_notification();
      button_sequence();

      if( (queued_command == STOP_BUTTONS) && (sequence_status == SEQUENCE_NOT_BUSY) ){
        estado_buttonSM = BUTTONS_INACTIVE;
        queued_command = NO_COMMAND;
      }
      break;
  
  }

  *inform_status = estado_buttonSM;
}
