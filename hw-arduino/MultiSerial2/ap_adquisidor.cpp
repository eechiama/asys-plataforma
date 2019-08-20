/* ========= include files =========== */
/* =================================== */
#include "ap_adquisidor.h"
#include "ap_uart.h"
#include "ap_filtro.h"
#include "pr_adc.h"
#include <Arduino.h>

/* ======== private constants ======== */
/* =================================== */

// PARA LA VARIABLE: estado_medidor
const int MEDIDOR_RESET = 0;
const int MEDIDOR_INACTIVO = 1;
const int MEDIDOR_ACTIVO = 2;

// Constantes para indicar la tx status de la señal de prueba
const int TX_DOING = 0;
const int TX_DONE = 1;

/* ======== private datatypes ======== */
/* =================================== */

/* ==== private global variables ===== */
/* =================================== */

static volatile uint32_t estado_medidor = MEDIDOR_RESET;

/* ==== shared global variables ====== */
/* =================================== */

/* ======= private prototypes ======== */
/* =================================== */

uint8_t tx_Test_Signal_1( void );
uint8_t tx_Test_Signal_2( void );
uint8_t tx_Test_Signal_3( void );

void enviar_muestra( uint16_t MuestraEfectiva );

/* ======= private functions ========= */
/* =================================== */

uint8_t tx_Test_Signal_1(){
  // sin ruido
  static uint8_t ecg1[] = { 90,  95, 124, 153, 182, 211, 241, 230, 202, 173, 143, 114,  89,  83,  75,  67,  70,  78,  85,  90,  90,  90,  90,  90,  92, 100, 107, 113, 118, 122, 124, 125, 124, 121, 117, 111, 104,  97,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  92,  93,  93,  92,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  97, 104, 109, 112, 113, 111, 107, 100,  91,  90,  90,  90,  90,  90,  90,  }  ; 
  static int inx = 0;
  static int arrayLength = sizeof(ecg1) / sizeof(ecg1[0]);

  delay(10);
  Serial.write( SYMBOL_START_OF_DATA_WORD );
  Serial.write( ecg1[inx] ); 
  Serial.write( SYMBOL_END_OF_WORD );
  inx++;
  inx %= arrayLength;

  if ( inx==0 ){
    return TX_DONE;
  }

  return TX_DOING;
}

uint8_t tx_Test_Signal_2(){
  // con ruido
  byte ecg2[] = { 94,  95, 128, 158, 187, 215, 245, 233, 202, 174, 144, 114,  94,  84,  77,  69,  72,  81,  85,  94,  93,  94,  92,  92,  92, 101, 110, 115, 123, 123, 129, 128, 127, 126, 118, 113, 107, 101,  94,  90,  91,  92,  90,  93,  92,  91,  91,  94,  95,  96,  98,  93,  94,  94,  93,  91,  93,  91,  91,  91,  94,  90,  91,  90,  92,  90,  94,  91,  90,  91,  99, 104, 114, 114, 114, 112, 108, 100,  94,  94,  93,  90,  90,  94,  94  };
  static int inx = 0;
  static int arrayLength = sizeof(ecg2) / sizeof(ecg2[0]);

  delay(10);
  Serial.write( SYMBOL_START_OF_DATA_WORD );
  Serial.write( ecg2[inx] ); 
  Serial.write( SYMBOL_END_OF_WORD );
  inx++;
  inx %= arrayLength;

  if ( inx==0 ){
    return TX_DONE;
  }

  return TX_DOING;
}

uint8_t tx_Test_Signal_3(){
  // con ruido
  byte ecg2[] = {   94,  95, 128, 158, 187, 215, 245, 233, 202, 174, 144, 114,  94,  84,  77,  69,  72,  81,  85,  94,  93,  94,  92,  92,  92, 101, 110, 115, 123, 123, 129, 128, 127, 126, 118, 113, 107, 101,  94,  90,  91,  92,  90,  93,  92,  91,  91,  94,  95,  96,  98,  93,  94,  94,  93,  91,  93,  91,  91,  91,  94,  90,  91,  90,  92,  90,  94,  91,  90,  91,  99, 104, 114, 114, 114, 112, 108, 100,  94,  94,  93,  90,  90,  94,  94  };
  static int inx = 0;
  static int arrayLength = sizeof(ecg2) / sizeof(ecg2[0]);
  byte a;

  delay(10);
  a = ecg2[inx] + random(0,5) ;
  Serial.write( SYMBOL_START_OF_DATA_WORD );
  Serial.write( a ); 
  Serial.write( SYMBOL_END_OF_WORD );
  inx++;
  inx %= arrayLength;

  if ( inx==0 ){
    return TX_DONE;
  }

  return TX_DOING;
}

void enviar_muestra( uint16_t MuestraEfectiva ) {

  Serial.write( SYMBOL_START_OF_DATA_WORD );
  Serial.write((uint8_t)((MuestraEfectiva>>8) & 0xF));    // envío primero los 4 bits más significativos
  Serial.write((uint8_t)(MuestraEfectiva & 0xFF));      // envío los 8 restantes
  Serial.write( SYMBOL_END_OF_WORD );

  return;
}

/* ======== public functions ========= */
/* =================================== */

void Controlador(void) {
  
  static uint8_t tx_signal_status = TX_DONE;
  static uint16_t value;

  // MdE: medición del ADC y transmisión de datos
  switch (estado_medidor) {

    case MEDIDOR_RESET:
      estado_medidor = MEDIDOR_INACTIVO;
      break;

    case MEDIDOR_INACTIVO:
      // caso: comando para iniciar muestreo
      if ( command == START_ADC ) {
        command = NO_COMMAND;
        estado_medidor = MEDIDOR_ACTIVO;
        buffer_reset();
        Start_Sampling();
        }
      // caso: comando para configurar Sample Rate
      if( command == CONFIG_SR ){
        command = NO_COMMAND;
        adc_sampleRate(rx_fmuestreo);
      }        
      // caso: comando para enviar señal de prueba 1.
      if( command == SEND_TEST_SIGNAL_1 ){
        tx_signal_status = tx_Test_Signal_1();
        if ( tx_signal_status == TX_DONE ){
          command = NO_COMMAND;
        }
      }
      // caso: comando para enviar señal de prueba 2.
      if( command == SEND_TEST_SIGNAL_2 ){
        tx_signal_status = tx_Test_Signal_2();
        if ( tx_signal_status == TX_DONE ){
          command = NO_COMMAND;
        }
      }
      // caso: comando para enviar señal de prueba 3.
      if( command == SEND_TEST_SIGNAL_3 ){
        tx_signal_status = tx_Test_Signal_3();
        if ( tx_signal_status == TX_DONE ){
          command = NO_COMMAND;
        }
      }
      break;
      
    case MEDIDOR_ACTIVO:
      // caso: muestra lista
      if( adc_read( &value ) ) {
        
        // Compilación condicional: Muestras filtradas
        #ifdef FILTRAR        
          if( queue_in_buffer( value ) == BUFFER_COMPLETED )  enviar_muestra( filtro_mediana() );
        #endif

        // Compilación condicional: Muestras sin filtrar
        #ifndef FILTRAR
          enviar_muestra( value );
        #endif
      }
        
      // caso: comando para detener muestreo
      if ( command == STOP_ADC ) {
        command = NO_COMMAND;
        estado_medidor = MEDIDOR_INACTIVO;
        Stop_Sampling();
      }
      break;
      
    default:
      estado_medidor = MEDIDOR_INACTIVO;
      break;
  }
}
