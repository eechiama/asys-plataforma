/*******************************************************************************************************************************//**
 *
 * @file		AP_UART_0.c
 * @brief		--Descripción del Módulo--
 * @date		Nov 12, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "AP_UART_0.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


// Para MDE de recepción de mensajes
#define ESPERANDO_TRAMA		0
#define RECIBIENDO_TRAMA	1
#define MAX_TRAMA_RX		8


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/


volatile uint8_t command = NO_COMMAND;
volatile char string_fmuestreo[] = {'2','5','0','0','\0'};
volatile char string_SelectedChannel = '2';
volatile uint16_t rx_fmuestreo = 2500;
volatile uint8_t rx_Channel=2;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void leer_comandos( const char msg_rx[] );


/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/


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
				string_fmuestreo[0] = ' ';
				string_fmuestreo[1] = ' ';
				string_fmuestreo[2] = trama[2];
				string_fmuestreo[3] = trama[3];
			}
			if( digitos == 3 ){
				rx_fmuestreo = ( trama[2]-48 ) * 100 + (trama[3]-48) * 10 + (trama[4]-48);
				string_fmuestreo[0] = ' ';
				string_fmuestreo[1] = trama[2];
				string_fmuestreo[2] = trama[3];
				string_fmuestreo[3] = trama[4];
			}
			if( digitos == 4){
				rx_fmuestreo = ( trama[2]-48 ) * 1000 + (trama[3]-48) * 100 + (trama[4]-48) * 10 + (trama[5]-48);
				string_fmuestreo[0] = trama[2];
				string_fmuestreo[1] = trama[3];
				string_fmuestreo[2] = trama[4];
				string_fmuestreo[3] = trama[5];
			}
			command = CONFIG_SR;
		}
	}

	// Comando para configurar el canal de entrada al ADC
	// Formato: I,X.
	// Donde X es la entrada de la placa Infotronic a configurar y puede ser 0, 1 o 2.
	if( (trama[0]) == 'I' ){
		if ( trama[1] == ',' && trama[3] == '.' ) {
			rx_Channel = trama[2] - 48;
			string_SelectedChannel = trama[2];
			command = CONFIG_INPUT;
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


/**********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/


void RX_Mensajes(void) {
	static uint8_t estado_rx = ESPERANDO_TRAMA;
	static char msg_rx[MAX_TRAMA_RX] = {0};
	static uint8_t inx_msg_rx = 0;

	uint8_t data;

	// Chequeo si llegó un msje...
	if ( U0_PopRx( &data ) ) {

		// MdE: Análisis de la trama recibida
		switch ( estado_rx ) {

			case ESPERANDO_TRAMA:
				// Espero el caracter de inicio de la trama ('$')
				if ( (char)data == '$' ) {
					inx_msg_rx = 0;
					estado_rx = RECIBIENDO_TRAMA;
				}
				break;

			case RECIBIENDO_TRAMA:
				// caso: no se llegó al fin de trama ('#'), recibo y almaceno.
				if ( (char)data != '#' ) {
					msg_rx[inx_msg_rx] = (char)data;
					inx_msg_rx++;
					if (inx_msg_rx > MAX_TRAMA_RX-1) {  // protección overflow
						estado_rx = ESPERANDO_TRAMA;
					}
					break;
				}
				// caso: se terminó de recibir la trama ('#')
				if ( (char)data == '#' ) {
					leer_comandos(msg_rx);
					estado_rx = ESPERANDO_TRAMA;
				}
				break;

			default:
				estado_rx = ESPERANDO_TRAMA;
				break;
		}
	}
}
