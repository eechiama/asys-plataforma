/**
 * @file	AP_ADQ_COMMANDS.c
 * @brief	x
 * @author	Esteban Chiama
 * @date	Aug 14, 2020
 * @version	1.0
 */

#include "../includes/AP_ADQ_COMMANDS.h"
#include <AP_DEBUG.h>

// Shared global variables
// ====================================
volatile commands_en command = NO_COMMAND;

volatile unsigned char rx_channel = 2;
volatile unsigned short int rx_sampleRate = 2500;

volatile unsigned short int rx_divider = 1;
volatile signal_sel_en rx_waveform = 0;
// =====================================

void command_interpreter( const unsigned char word[] ){
	unsigned char digits = 0;

	// Command:	Start/Stop sampling.
	// Format:	MX
	// X can be:	'0' stop, '1' start
	if ((word[0]) == 'M') {

		if((word[1]) == '0') {
			command = ADC_STOP;
		}
		else if ((word[1]) == '1') {
			command = ADC_START;
		}
	}

	// Command:	Set ADC input channel.
	// Format:	I,X.
	// X refers to Infotronic's board 'Entrada Analógica' input.
	// It can be:	0, 1 or 2.
	// Representing EA0, EA1, EA2.
	if( (word[0]) == 'I' ){
		if ( word[1] == ',' && word[3] == '.' ) {
			rx_channel = word[2] - 48;
			command = CONFIG_INPUT;
		}
	}

	// Command:	Set ADC sample rate.
	// Format:	C,XXXX.
	// Where XXXX is the frequency to set.
	// It can be 2, 3 or 4 digits long.
	if( (word[0] == 'C') && (word[1] == ',') ){

		// Cantidad de dígitos del sample rate y validación del comando
		digits = 2;
		if( word[4] != '.' ){
			digits++;
			if( word[5] != '.' ){
				digits++;
				if( word[6] != '.' ){
					// Comando inválido, más de 4 dígitos o no tiene el punto
					digits = 0;
				}
			}
		}

		if( digits != 0 ){

			if( digits == 2 ){
				rx_sampleRate = ( word[2]-48 ) * 10 + (word[3]-48) ;
			}
			if( digits == 3 ){
				rx_sampleRate = ( word[2]-48 ) * 100 + (word[3]-48) * 10 + (word[4]-48);
			}
			if( digits == 4){
				rx_sampleRate = ( word[2]-48 ) * 1000 + (word[3]-48) * 100 + (word[4]-48) * 10 + (word[5]-48);
			}
			command = CONFIG_SR;
		}
	}

	// Command:	Send a test signal.
	// Format:	TX
	// Where X is a number that specifies the signal to send.
	if( (word[0]) == 'T' ){
		if ( word[1] == '1' ) {
			command = SEND_TEST_SIGNAL_1;
		}
		if ( word[1] == '2' ) {
			command = SEND_TEST_SIGNAL_2;
		}
	}

	// Comando para activar el generador de señales.
	// Formato: P1,X,YYY.
	// Donde X refiere al tipo de señal:
	//		S = seno,
	//		R = rampa,
	//		Q = square
	// YYY refiere al divisor de frecuencia (debe ser un num entre 1 y 999)
	if ( (word[0] == 'P') && (word[1] == '1') && (word[2] == ',') && (word[4] == ',') ) {
	digits = 1;
	if ( word[6] != '.' ) digits++;
	if ( word[7] != '.' ) digits++;

	if ( digits == 1 ) {
		rx_divider = word[5] - 48;
	}
	if ( digits == 2 ) {
		rx_divider = ( word[5] - 48 ) * 10 + (word[6] - 48);
	}
	if ( digits == 3 ) {
		rx_divider = ( word[5] - 48 ) * 100 + (word[6] - 48) * 10 + (word[7] - 48);
	}

	if ( word[3] == 'S' ){
		rx_waveform = SINEWAVE;
	}
	else if ( word[3] == 'R' ){
		rx_waveform = RAMP;
	}
	else if ( word[3] == 'Q' ){
		rx_waveform = SQUARE;
	}
	else{
		rx_waveform = SINEWAVE; // default
	}
	command = GENERATOR_START;
	}

	// Comando para desactivar la salida de PWM
	// Formato: P0
	if ( (word[0] == 'P') && (word[1] == '0') ) {
		command = GENERATOR_STOP;
	}
}
