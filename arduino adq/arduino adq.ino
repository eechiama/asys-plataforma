#include "ap_adquisidor.h"
#include "ap_generator.h"
#include "ap_buttons.h"
#include "ap_uart.h"
#include "dr_adc.h"
#include "dr_timer2_pwm.h"

const long BAUD_RATE = 115200;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);
  
  adc_init();
  timer1_init();  // para el adc
  timer2_pwm_init();
}

void loop(){
  
  int i;
  for(i=1 ;i<2 ; i++){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }

  uint8_t buttonMDE_state = NO_STATE;

  while(1) {
   Controlador();
   Generator();
   RX_Mensajes(buttonMDE_state);
   Buttons(&buttonMDE_state);
  }
}
