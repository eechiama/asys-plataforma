#ifndef AP_UART_H
#define AP_UART_H

/* ===== include files ===== */
/* ========================= */
#include <Arduino.h>

/* ======= constants ======= */
/* ========================= */

// PARA LA VARIABLE: command
// ADC
const int NO_COMMAND = 10;
const int START_ADC = 11;
const int STOP_ADC = 12;
const int CONFIG_SR = 16;
// Test Signals
const int SEND_TEST_SIGNAL_1 = 13;
const int SEND_TEST_SIGNAL_2 = 14;
const int SEND_TEST_SIGNAL_3 = 15;
// PWM
const int PWM_SINE = 20;
const int PWM_RAMP = 21;
const int PWM_HIGH = 22;
const int PWM_SQUARE = 23;
const int PWM_ECG = 24;
const int PWM_OFF = 30;

// PROTOCOLO DE COMUNICACIÓN
const int SYMBOL_END_OF_WORD = '#';
const int SYMBOL_START_OF_COMMAND_WORD = '$';
const int SYMBOL_START_OF_DATA_WORD = '%';

/* ======= datatypes ======= */
/* ========================= */

/* === public variables ==== */
/* ========================= */

extern volatile uint8_t command;
extern volatile uint16_t rx_fmuestreo;
extern volatile uint8_t rx_pwm_divider;

/* === public functions ==== */
/* ========================= */
void RX_Mensajes(void);

#endif /* AP_UART_H */
