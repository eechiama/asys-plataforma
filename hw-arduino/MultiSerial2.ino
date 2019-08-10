#include <TimerOne.h>

#include "constantes.h"

const byte adcPin = 0;  // A0

// Estados
static uint32_t estado_medidor = MEDIDOR_RESET;
static uint8_t command = NO_COMMAND;

// FLAGS
volatile uint8_t ADC_dato_disponible = 0;
volatile uint16_t ADC_valor = 0;

// Variables de configuración
static uint16_t rx_fmuestreo = 2500;

// Variables globales (PR_ADC)
volatile uint16_t BufferMuestras[SIZE];
static uint8_t inxBuffer = 0;



void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);

  Timer1.initialize(PERIOD_DEFAULT);  // en microsegundos. Puesto para muestrear a 2500Hz.
  Timer1.attachInterrupt(TimerCallback);

  // ADC Setup
  ADMUX =   bit (REFS0) | (adcPin & 0x07);  
  ADCSRA =  bit (ADEN); // peripheral on
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // prescaler en 128. ADC Clock Freq 125kHz.  1 conversión lleva 13 ciclos de adc clock.
  ADCSRA |= bit(ADIE);  // habilito las interrupciones.
  
}

void loop(){
  
  int i;
  
  for(i=1 ;i<2 ; i++){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }
  
  Serial.write( "Hola Mundo !" );
  
  while(1) {

   Controlador();
   RX_Mensajes();
   
  }

}

/***************************/
/* FUNCIONES DE APLICACION */
/***************************/

void Controlador(void) {
  
  static uint8_t tx_signal_status = TX_DONE;

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
        ResetBuffer();
        Start_Sampling();
        }
      // caso: comando para configurar Sample Rate
      if( command == CONFIG_SR ){
        command = NO_COMMAND;
        ADC_Timer0_Config(rx_fmuestreo);
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
      // caso: muestra lista, la envío por el puerto serie
      if ( ADC_dato_disponible ) {
        ADC_dato_disponible = 0;
        Preparar_y_Enviar();
        // transmito la trama con un nuevo dato
//              Serial.write( '#' ); // 35
//              Serial.write((uint8_t)(ADC_valor>>8) & 0xFF); // envío primero los 4 bits más significativos
//              Serial.write((uint8_t)(ADC_valor & 0xFF)); // envío los 8 restantes
//              Serial.write( '$' ); // 36
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

void RX_Mensajes(void){

  static uint8_t inx_msg_rx = 0;
  static char trama_rx[MAX_TRAMA_RX]={0};
  static uint8_t estado_rx = ESPERANDO_TRAMA ;

  if (Serial.available()) {
    int inByte = Serial.read(); 
      switch ( estado_rx ) {
        case ESPERANDO_TRAMA:
          if(inByte=='$'){
          inx_msg_rx = 0;
          estado_rx = RECIBIENDO_TRAMA ;
          }
          break;
            
        case RECIBIENDO_TRAMA:
        // caso: en medio de la trama
         if( inByte != '#'){
          trama_rx[inx_msg_rx] = inByte;
          inx_msg_rx++;
          if (inx_msg_rx > MAX_TRAMA_RX-1){ // PROTECCIÓN OVERFLOW. TRAMA QUE LLEGó AL MÁXIMO DE 8 BYTES SIN CARACTER DE FIN '#'
            estado_rx = ESPERANDO_TRAMA;
          }
          break;
         }
         // caso: fin de la trama
         if(inByte == '#'){
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
  if( (trama[0]) == 'C'  && estado_medidor == MEDIDOR_INACTIVO){
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
  if( (trama[0]) == 'T' && estado_medidor == MEDIDOR_INACTIVO){
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

uint8_t tx_Test_Signal_1(){
  // sin ruido
  static uint8_t ecg1[] = { 90,  95, 124, 153, 182, 211, 241, 230, 202, 173, 143, 114,  89,  83,  75,  67,  70,  78,  85,  90,  90,  90,  90,  90,  92, 100, 107, 113, 118, 122, 124, 125, 124, 121, 117, 111, 104,  97,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  92,  93,  93,  92,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  90,  97, 104, 109, 112, 113, 111, 107, 100,  91,  90,  90,  90,  90,  90,  90,  }  ; 
  static int inx = 0;
  static int arrayLength = sizeof(ecg1) / sizeof(ecg1[0]);

  delay(10);
  Serial.write( 35 );
  Serial.write( ecg1[inx] ); 
  Serial.write( 36 );
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
  Serial.write( 35 );
  Serial.write( ecg2[inx] ); 
  Serial.write( 36 );
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
  Serial.write( 35 );
  Serial.write( a ); 
  Serial.write( 36 );
  inx++;
  inx %= arrayLength;

  if ( inx==0 ){
    return TX_DONE;
  }

  return TX_DOING;
}



/************/
/* DR_ADC.c */
/************/



void Start_Sampling(){
  Timer1.start();
}

void Stop_Sampling(){
  Timer1.stop();
}

void ADC_Timer0_Config(uint16_t s_rate){
  double microseg = (double)1/(double)1000000;
  double Ts=0;
  uint32_t cantidad_microsegundos=0;

  Ts = (double)1 / (double)s_rate ;

  cantidad_microsegundos = (uint32_t) ( Ts / microseg )  ;

  Timer1.initialize(cantidad_microsegundos);
}

void TimerCallback(){
  // Disparo una conversión.
  ADC_Convert_Start();
}

void ADC_Convert_Start(void){
  // Empiezo una conversión.
  ADCSRA |= bit (ADSC);
}

ISR (ADC_vect) {

  // leo el resultado
  uint16_t adcReading = ADC;
  
  ADC_valor = adcReading;
  ADC_dato_disponible = 1;

}



/**********/
/* PR_ADC */
/**********/




void ResetBuffer( void ){

  // Simplemente que se vuelva a escribir desde la posición 0
  inxBuffer = 0;

}

uint8_t GetBufferStatus(void){

  uint8_t bufferStatus = ENLISTANDO;

  if ( inxBuffer == SIZE ){
    inxBuffer = 0;
    bufferStatus = VECTORES_LLENOS;
  }

  return bufferStatus;
}


void Enlistar( void ){

  uint16_t sample = ADC_valor;

  BufferMuestras[inxBuffer] = sample;
  inxBuffer++;

}


uint16_t Mediana_de_Buffer( void ){

  uint16_t MuestraEfectiva;

  // Ordenamos el vector
  bubble(BufferMuestras,SIZE);

  // Calculamos la media
  MuestraEfectiva = ( BufferMuestras[(SIZE-1)/2] + BufferMuestras[SIZE/2] ) / 2;

  return MuestraEfectiva;
}


/* Funcion bubble, que ordena un vector de menor a mayor con el metodo de burbujeo.*/
void bubble(volatile uint16_t *vector, int size) {

  int aux; //para el swap.
  int i, j;

  for(j=0; j<size-1; j++) {

    for(i=0; i<size-1-j; i++) {

      if(vector[i]>vector[i+1]) {
        aux = vector[i+1];
        vector[i+1] = vector[i];
        vector[i] = aux;
      }

    }

  }
}




/**********/
/* AP_ADC */
/**********/



void Preparar_y_Enviar( void ){

  uint8_t bufferStatus, flag_Enviar = 0;
  uint16_t MuestraEfectiva;

  bufferStatus = GetBufferStatus();
  if( bufferStatus ==  VECTORES_LLENOS ){
    if ( SIZE != 1 ) {
      MuestraEfectiva = Mediana_de_Buffer();
    }
    else {
      MuestraEfectiva = ADC_valor;
    }
    flag_Enviar = 1;
  }

  Enlistar();

  if( flag_Enviar == 1 ){
    // transmito la trama con una muestra
    EnviarMuestra( MuestraEfectiva );
  }

}

void EnviarMuestra( uint16_t MuestraEfectiva ) {

  Serial.write('#');
  Serial.write((uint8_t)((MuestraEfectiva>>8) & 0xF));    // envío primero los 4 bits más significativos
  Serial.write((uint8_t)(MuestraEfectiva & 0xFF));      // envío los 8 restantes
  Serial.write('$');

  return;
}
