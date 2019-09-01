/*******************************************************************************************************************************//**
 *
 * @file		AP_Adquisidor_MDE.c
 * @brief		--Descripción del Módulo--
 * @date		xx/xx/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "AP_Adquisidor_MDE.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


// Constantes para el estado del medidor
#define MEDIDOR_RESET		0
#define	MEDIDOR_INACTIVO	1
#define	MEDIDOR_ACTIVO		2


// Constantes para indicar la tx status de la señal de prueba
#define TX_DOING	0
#define TX_DONE		1


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

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


static volatile uint32_t estado_medidor = MEDIDOR_RESET;


/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


uint8_t tx_Test_Signal_1( void );
uint8_t tx_Test_Signal_2( void );


 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


uint8_t tx_Test_Signal_1(){
	static uint8_t signal[] = { 90, 95, 124, 153, 182, 211, 241, 230, 202, 173, 143, 114, 89, 83, 75, 67, 70, 78, 85, 90, 90, 90, 90, 90, 92, 100, 107, 113, 118, 122, 124, 125, 124, 121, 117, 111, 104, 97, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 92, 93, 93, 92, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 97, 104, 109, 112, 113, 111, 107, 100, 91, 90, 90, 90, 90, 90, 90, 90, 95, 124, 153, 182, 211, 241, 230, 202, 173, 143, 114, 89, 83, 75, 67, 70, 78, 85, 90, 90, 90, 90, 90, 92, 100, 107, 113, 118, 122, 124, 125, 124, 121,	117, 111, 104, 97, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 92, 93, 93, 92, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 97, 104, 109, 112, 113, 111, 107, 100, 91, 90, 90, 90, 90, 90, 90, 90, 95, 124, 153, 182, 211, 241, 230, 202, 173, 143, 114, 89, 83, 75, 67, 70, 78, 85, 90, 90, 90, 90, 90, 92, 100, 107, 113, 118, 122};
	static int inx = 0;
	static int arrayLength = sizeof(signal) / sizeof(signal[0]);
	int i=0;

	i=0;
	while (i<10000){
		i++;
	}

	U0_PushTx('#');
	U0_PushTx((uint8_t) signal[inx]);
	U0_PushTx('$');
	inx++;
	inx %= arrayLength;

	if ( inx==0 ){
		return TX_DONE;
	}

	return TX_DOING;
}


uint8_t tx_Test_Signal_2(){
	static uint8_t signal[] = { 94, 95, 128, 158, 187, 215, 245, 233, 202, 174, 144, 114,  94,  84,  77,  69,  72,  81,  85,  94,  93,  94,  92,  92,  92, 101, 110, 115, 123, 123, 129, 128, 127, 126, 118, 113, 107, 101,  94,  90,  91,  92,  90,  93,  92,  91,  91,  94,  95,  96,  98,  93,  94,  94,  93,  91,  93,  91,  91,  91,  94,  90,  91,  90,  92,  90,  94,  91,  90,  91,  99, 104, 114, 114, 114, 112, 108, 100,  94,  94,  93,  90,  90,  94,  94  };
	static int inx = 0;
	static int arrayLength = sizeof(signal) / sizeof(signal[0]);
	int i=0;

	i=0;
	while (i<10000){
		i++;
	}

	U0_PushTx('#');
	U0_PushTx((uint8_t) signal[inx]);
	U0_PushTx('$');
	inx++;
	inx %= arrayLength;

	if ( inx==0 ){
		return TX_DONE;
	}

	return TX_DOING;
}


 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


void MDE_Adquisidor(void) {
	static char msg_LCD[2*LARGO_RENGLON];
	static uint8_t tx_signal_status = TX_DONE;

	// MdE: medición del ADC y transmisión de datos
	switch (estado_medidor) {

		case MEDIDOR_RESET:
			LCD_DisplayMsg("> INACTIVO.     ", LCD_RENGLON_1, 0);
			LCD_DisplayMsg("> ASyS CL2018-19", LCD_RENGLON_2, 0);
			estado_medidor = MEDIDOR_INACTIVO;
			break;

		case MEDIDOR_INACTIVO:
			// caso: comando para iniciar muestreo
			if ( command == START_ADC && tx_signal_status == TX_DONE) {
				command = NO_COMMAND;
				estado_medidor = MEDIDOR_ACTIVO;
				if( !is_ADC_ON() ){
					ResetBuffer();
					Start_Sampling();
					LCD_DisplayMsg("> MUESTREANDO.  ", LCD_RENGLON_1, 0);
					IO_LED_Set(IO_LED_STICK, ON);
				}
			}
			// caso: comando para configurar Sample Rate
			if( command == CONFIG_SR ){
				command = NO_COMMAND;
				ADC_Timer0_Config(rx_fmuestreo);
				sprintf(msg_LCD, "> In=%c Fs=%sHz   ", string_SelectedChannel, string_fmuestreo);
				LCD_DisplayMsg(msg_LCD, LCD_RENGLON_2, 0);
			}
			// caso: comando para configurar el canal de entrada
			if( command == CONFIG_INPUT ){
				command = NO_COMMAND;
				ADC_InputSelect(rx_Channel);
				sprintf(msg_LCD, "> In=%c Fs=%sHz   ", string_SelectedChannel, string_fmuestreo);
				LCD_DisplayMsg(msg_LCD, LCD_RENGLON_2, 0);
			}
			// caso: comando para enviar la señal de prueba 1.
			if( command == SEND_TEST_SIGNAL_1 ){
				tx_signal_status = tx_Test_Signal_1();
				if ( tx_signal_status == TX_DONE ){
					command = NO_COMMAND;
					LCD_DisplayMsg("> TX T.SIGNAL OK", LCD_RENGLON_2, 0);
				}
			}
			// caso: comando para enviar la señal de prueba 2.
			if( command == SEND_TEST_SIGNAL_2 ){
				tx_signal_status = tx_Test_Signal_2();
				if ( tx_signal_status == TX_DONE ){
					command = NO_COMMAND;
					LCD_DisplayMsg("> TX T.SIGNAL OK", LCD_RENGLON_2, 0);
				}
			}
			break;


		case MEDIDOR_ACTIVO:
			// caso: muestra lista, la envío por el puerto serie
			if (ADC_dato_disponible) {
				ADC_dato_disponible = 0;
				Preparar_y_Enviar();
//				// transmito la trama con un nuevo dato
//				PushTx('#');
//				PushTx((uint8_t)((ADC_valor>>8) & 0xFF));		// envío primero los 4 bits más significativos
//				PushTx((uint8_t)(ADC_valor & 0xFF));			// envío los 8 restantes
//				PushTx('$');
			}
			// caso: comando para detener muestreo
			if ( command == STOP_ADC ) {
				command = NO_COMMAND;
				estado_medidor = MEDIDOR_INACTIVO;
				Stop_Sampling();
				LCD_DisplayMsg("> INACTIVO     ", LCD_RENGLON_1, 0);
				sprintf(msg_LCD, "> In=%c Fs=%sHz   ", string_SelectedChannel, string_fmuestreo);
				LCD_DisplayMsg(msg_LCD, LCD_RENGLON_2, 0);
				IO_LED_Set(IO_LED_STICK, OFF);
			}
			// actualizo el valor mostrado en el LCD
			if (flag_updateValorLCD) {
				flag_updateValorLCD  = 0;
				sprintf(msg_LCD, "%sHz. Val=%04d", string_fmuestreo, ADC_valor);
				LCD_DisplayMsg(msg_LCD, LCD_RENGLON_2, 0);
			}
			break;
		default:
			estado_medidor = MEDIDOR_INACTIVO;
			break;
	}
}
