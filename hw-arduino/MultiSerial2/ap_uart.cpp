/* ========= include files =========== */
/* =================================== */
#include "ap_uart.h"

/* ======== private constants ======== */
/* =================================== */

// estados para la MDE de recepción de mensajes
const int ESPERANDO_TRAMA = 0;
const int RECIBIENDO_TRAMA = 1;

const int MAX_TRAMA_RX = 8;

/* ======== private datatypes ======== */
/* =================================== */

/* ==== private global variables ===== */
/* =================================== */

/* ==== shared global variables ====== */
/* =================================== */
volatile uint8_t command = NO_COMMAND;
volatile uint16_t rx_fmuestreo = 2500;

/* ======= private prototypes ======== */
/* =================================== */
void leer_comandos( const char msg_rx[] );

/* ======= private functions ========= */
/* =================================== */
void leer_comandos( const char trama[] ){
  
    uint8_t digitos=0;

  // Comando para el muestreo
  // Formato: MX
  // Donde X puede ser: '0' detener, '1' iniciar
  if ((trama[0]) == 'M') {

    if((trama[1]) == '0') {
      command = STOP_ADC;
    }

    else if ((trama[1]) == '1') {
      command = START_ADC;
    }
  }

  // Comando para configurar frecuencia de muestreo
  // Formato: C,XXXX.
  // Donde XXXX es la frecuencia a configurar, y puede ser de 2, 3 o 4 dígitos
  if( (trama[0]) == 'C' ){
    if ( trama[1] == ',' ) {
      digitos = 2;
      if( trama[4] != '.' ){
        digitos++;
        if( trama[5] != '.' ){
          digitos++;
        }
      }
      
      if( digitos == 2 ){
        rx_fmuestreo = ( trama[2]-48 ) * 10 + (trama[3]-48) ;
      }
      if( digitos == 3 ){
        rx_fmuestreo = ( trama[2]-48 ) * 100 + (trama[3]-48) * 10 + (trama[4]-48);
      }
      if( digitos == 4){
        rx_fmuestreo = ( trama[2]-48 ) * 1000 + (trama[3]-48) * 100 + (trama[4]-48) * 10 + (trama[5]-48);
      }
      command = CONFIG_SR;
    }
  }  

  // Comando para enviar una señal de prueba.
  // Formato: TX
  // Donde X es la entrada de la placa Infotronic a configurar y puede ser 0, 1 o 2.
  if( (trama[0]) == 'T' ){
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

}

/* ======== public functions ========= */
/* =================================== */

void RX_Mensajes(void){

  static uint8_t inx_msg_rx = 0;
  static char trama_rx[MAX_TRAMA_RX]={0};
  static uint8_t estado_rx = ESPERANDO_TRAMA ;

  if (Serial.available()) {
    int inByte = Serial.read(); 
      switch ( estado_rx ) {
        case ESPERANDO_TRAMA:
          if( inByte == SYMBOL_START_OF_COMMAND_WORD ){
          inx_msg_rx = 0;
          estado_rx = RECIBIENDO_TRAMA ;
          }
          break;
            
        case RECIBIENDO_TRAMA:
        // caso: en medio de la trama
         if( inByte != SYMBOL_END_OF_WORD){
          trama_rx[inx_msg_rx] = inByte;
          inx_msg_rx++;
          if (inx_msg_rx > MAX_TRAMA_RX-1){ // PROTECCIÓN OVERFLOW. TRAMA QUE LLEGó AL MÁXIMO DE 8 BYTES SIN CARACTER DE FIN
            estado_rx = ESPERANDO_TRAMA;
          }
          break;
         }
         // caso: fin de la trama
         if(inByte == SYMBOL_END_OF_WORD){
          leer_comandos(trama_rx);
          estado_rx = ESPERANDO_TRAMA;              
          }
         break;
              
        default:
            estado_rx = ESPERANDO_TRAMA;
        break;
      }   
  }
}
