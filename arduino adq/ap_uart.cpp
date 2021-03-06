#include "ap_uart.h"
#include "ap_buttons.h"

// estados para la MDE de recepción de mensajes
const int ESPERANDO_TRAMA = 0;

const int RECIBIENDO_TRAMA = 1;

const int MAX_TRAMA_RX = 9;

/* ==== shared global variables ====== */
/* =================================== */
volatile uint8_t command = NO_COMMAND;

volatile uint16_t rx_fmuestreo = 2500;

volatile uint16_t rx_pwm_divider = 1;

volatile uint8_t inx_waveform_command = 0;

/* ======= private prototypes ======== */
/* =================================== */
void leer_comandos( const char msg_rx[], const uint8_t button_status_lock );

/* ======= private functions ========= */
/* =================================== */
void leer_comandos( const char trama[], const uint8_t button_status_lock ) {

  uint8_t digitos = 0;

  // Comando para el muestreo
  // Formato: MX
  // Donde X puede ser: '0' detener, '1' iniciar
  if ((trama[0]) == 'M') {

    if ((trama[1]) == '0') {
      command = STOP_ADC;
    }

    else if ((trama[1]) == '1') {
      command = START_ADC;
    }
  }

  // Comando para configurar frecuencia de muestreo
  // Formato: C,XXXX.
  // Donde XXXX es la frecuencia a configurar, y puede ser de 2, 3 o 4 dígitos
  if ( (trama[0]) == 'C' ) {
    if ( trama[1] == ',' ) {
      digitos = 2;
      if ( trama[4] != '.' ) {
        digitos++;
        if ( trama[5] != '.' ) {
          digitos++;
        }
      }

      if ( digitos == 2 ) {
        rx_fmuestreo = ( trama[2] - 48 ) * 10 + (trama[3] - 48) ;
      }
      if ( digitos == 3 ) {
        rx_fmuestreo = ( trama[2] - 48 ) * 100 + (trama[3] - 48) * 10 + (trama[4] - 48);
      }
      if ( digitos == 4) {
        rx_fmuestreo = ( trama[2] - 48 ) * 1000 + (trama[3] - 48) * 100 + (trama[4] - 48) * 10 + (trama[5] - 48);
      }
      command = CONFIG_SR;
    }
  }

  // Comando para enviar una señal de prueba.
  // Formato: TX
  // Donde X es la entrada de la placa Infotronic a configurar y puede ser 0, 1 o 2.
  if ( (trama[0]) == 'T' ) {
    if ( trama[1] == '1' ) {
      command = SEND_TEST_SIGNAL_1;
    }
    if ( trama[1] == '2' ) {
      command = SEND_TEST_SIGNAL_2;
    }
    if ( trama[1] == '3' ) {
      command = SEND_TEST_SIGNAL_3;
    }
  }

  // Comando para activar la salida de PWM con una señal modulada
  // Formato: P1,X,YYY.
  // Donde X refiere al tipo de señal. S = seno, R = rampa, H = HIGH (continua, valor lógico alto)
  if ( (trama[0] == 'P') && (trama[1] == '1') && (trama[2] == ',') && (trama[4] == ',') ) {
    digitos = 1;
    if ( trama[6] != '.' ) digitos++;
    if ( trama[7] != '.' ) digitos++;

    if ( digitos == 1 ) {
      rx_pwm_divider = trama[5] - 48;
    }
    if ( digitos == 2 ) {
      rx_pwm_divider = ( trama[5] - 48 ) * 10 + (trama[6] - 48);
    }
    if ( digitos == 3 ) {
      rx_pwm_divider = ( trama[5] - 48 ) * 100 + (trama[6] - 48) * 10 + (trama[7] - 48);
    }

    if ( trama[3] == 'S' )  command = PWM_SINE;
    
    if ( trama[3] == 'R' )  command = PWM_RAMP;
    
    if ( trama[3] == 'H' )  command = PWM_HIGH;
    
    if ( trama[3] == 'Q' )  command = PWM_SQUARE;
    
    if ( trama[3] == 'E' )  command = PWM_ECG;
    
    if ( trama[3] == 'I' )  command = PWM_IMPULSE;
    
  }

  // Comando para desactivar la salida de PWM
  // Formato: P0
  if ( (trama[0] == 'P') && (trama[1] == '0') ) {
    command = PWM_OFF;
  }

  // Comando para activar el modo Botones
  // Formato: B1,X,YY.
  // Donde X refiere al tipo de señal. S = seno, R = rampa, H = HIGH (continua, valor lógico alto)
  if ( (trama[0] == 'B') && (trama[1] == '1') && (trama[2] == ',') && (trama[4] == ',') ) {
    digitos = 1;
    if ( trama[6] != '.' ) digitos++;
    if ( trama[7] != '.' ) digitos++;

    if ( digitos == 1 ) {
      rx_pwm_divider = trama[5] - 48;
    }
    if ( digitos == 2 ) {
      rx_pwm_divider = ( trama[5] - 48 ) * 10 + (trama[6] - 48);
    }
    if ( digitos == 3 ) {
      rx_pwm_divider = ( trama[5] - 48 ) * 100 + (trama[6] - 48) * 10 + (trama[7] - 48);
    }

    if ( trama[3] == 'S' ) inx_waveform_command = 0;     // PWM_SINE
    
    if ( trama[3] == 'R' ) inx_waveform_command = 1;     // PWM_RAMP
    
    if ( trama[3] == 'Q' ) inx_waveform_command = 2;     // PWM_SQUARE
    
    if ( trama[3] == 'I' ) inx_waveform_command = 3;     // PWM_IMPULSE

    command = START_BUTTONS;
  }

  // Ignoro todos los comandos anteriores si estaba operando en el modo de los botones.
  if ( button_status_lock == BUTTONS_ACTIVE ) {
    command = NO_COMMAND;
  }

  // Comando para desactivar el modo Botones
  // Formato: B0
  if ( (trama[0] == 'B') && (trama[1]) == '0') {
    command = STOP_BUTTONS;
  }

}

/* ======== public functions ========= */
/* =================================== */

void RX_Mensajes(const uint8_t lock) {

  static uint8_t inx_msg_rx = 0;
  static char trama_rx[MAX_TRAMA_RX] = {0};
  static uint8_t estado_rx = ESPERANDO_TRAMA ;

  if (Serial.available()) {
    int inByte = Serial.read();
    switch ( estado_rx ) {
      case ESPERANDO_TRAMA:
        if ( inByte == SYMBOL_START_OF_COMMAND_WORD ) {
          inx_msg_rx = 0;
          estado_rx = RECIBIENDO_TRAMA ;
        }
        break;

      case RECIBIENDO_TRAMA:
        // caso: en medio de la trama
        if ( inByte != SYMBOL_END_OF_WORD ) {

          if (inx_msg_rx >= MAX_TRAMA_RX) {  // PROTECCIÓN OVERFLOW. TRAMA QUE SUPERÓ EL MÁXIMO DE 8 BYTES SIN CARACTER DE FIN
            estado_rx = ESPERANDO_TRAMA;
            break;
          }
          else {
            trama_rx[inx_msg_rx] = inByte;
            inx_msg_rx++;
          }
        }
        // caso: fin de la trama
        if ( inByte == SYMBOL_END_OF_WORD ) {
          leer_comandos(trama_rx, lock);
          estado_rx = ESPERANDO_TRAMA;
        }
        break;

      default:
        estado_rx = ESPERANDO_TRAMA;
        break;
    }
  }
}
