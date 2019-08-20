#include "ap_adquisidor.h"
#include "ap_uart.h"
#include "dr_adc.h"

const long BAUD_RATE = 115200;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);
  
  adc_init();
  timer1_init();
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
