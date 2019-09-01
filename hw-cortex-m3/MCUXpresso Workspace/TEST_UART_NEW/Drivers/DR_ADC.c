/*******************************************************************************************************************************//**
 *
 * @file		DR_ADC.c
 * @brief		--Descripción del Módulo--
 * @date		xx/xx/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "DR_ADC.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/


static uint16_t fmuestreo = 2500;


static uint8_t analogIn = 2;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/


volatile uint16_t ADC_valor;


volatile uint8_t ADC_dato_disponible;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void ADC_Start(void);


void ADC_Stop(void);


 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void TIMER0_IRQHandler(void){
	// Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );		// OKAY
	// Disparo una conversión.
	ADC_Start();
	// Saco el estado reset. Es necesario esto ?
	T0TCR &= ~( (0x1)<<1 );
}


void ADC_InputSelect(uint8_t selectedInput){
	uint8_t shift;
	uint8_t port, pin, pin_function;

	analogIn = selectedInput;

	if( analogIn == 0){
		shift = 5;
		port = P1;
		pin = 31;
		pin_function = PINSEL_FUNC3;
	}

	if( analogIn == 1){
		shift = 1;
		port = P0;
		pin = 24;
		pin_function = PINSEL_FUNC1;
	}

	if( analogIn == 2){
		shift = 2;
		port = P0;
		pin = 25;
		pin_function = PINSEL_FUNC1;
	}

	// 5. Config pines para entrada ADC0.2 (pin P0.25)
	SetPINSEL(port, pin, pin_function);
	SetResistorMode(port, pin, PINMODE_TRISTATE);	// Del manual: The PINMODE should be neither pull-up nor pull-down resistor enabled.
//	SetDIR(port, pin, 0);	// Configuro el pin del adc como entrada

	// 6. Selecciono que voy a tomar muestras del canal especificado
	AD0CR &= ~(0xFF);			// Debe haber solo 1 pin en alto. Por las dudas, todos en 0 primero.
	AD0CR |= (0x01<<shift);		// Pongo AD0.x en alto

	// 7. Sobre la alerta de interrupcione
	AD0INTEN &= ~(0xFF);			// Primero pongo todos en 0 por las dudas.
	AD0INTEN |= (0x01<<shift);		// Habilito interrupción que alerte sobre conversión del canal AD0.x
	AD0INTEN &= ~( (0x1)<<8 );		// Solamente los canales habilitados en este registro pueden generar interrupciones.
}


void ADC_Start(void){
	/* Empieza una conversión de modo Software-Controlled */
	AD0CR |= (0x01<<24);
}


void ADC_Stop(void){
	/* Detiene una conversión de modo Software-Controlled */
	AD0CR &= ~( (0x7)<<24 );
}


void ADC_IRQHandler(void){
	uint32_t adc_data_reg = 0;

	// leo el registro de resultado
	if(analogIn == 2){
		adc_data_reg = AD0DR2;
	}
	else if(analogIn == 1){
		adc_data_reg = AD0DR1;
	}
	else if(analogIn == 0){
		adc_data_reg = AD0DR5;
	}

	// chequeo bit DONE == 1 -> hay un resultado disponible
	if ( (adc_data_reg >> 31) == 0x01 ) {

		ADC_valor = (adc_data_reg >> 4) & 0xFFF;
		ADC_dato_disponible = 1;

	}

}


 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


void ADC_Timer0_Init( void ){

	// 1. Alimentar el timer.
	PCONP |= ( (0x1)<<1 );			// OKAY

	// 2. Set up PCLK del timer. Bits 2:3 == 00 => CCLK/4. 25MHz.
	PCLKSEL0 &= ~( (0x3)<<2 );		// OKAY

	// 3. Seleciono modo Timer. Bits 0:1 == 00
	*T0CTCR &=  ~( (0x3)<<0 );		// OKAY

	// 3. Configuro el prescale, y el max. timer count
	ADC_Timer0_Config(fmuestreo);

	// Detengo el timer.
	T0TCR &= ~( (0x1)<<0 );			// OKAY
	// Pongo el timer en estado RESET.
	T0TCR |= ( (0x1)<<1 );			// OKAY

	// 4. Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );			// OKAY

	// 5. Habilito la interrupción correspondiente al TIMER0 en el NVIC. Bit 1 == 1
	ISER0 |= ( (0x1)<<1 );			// OKAY

	// 7. Config de acción cuando el TC == MATCH
	T0MCR |= ( (0x1)<<0 );	// Interrupción ON.			OKAY
	T0MCR |= ( (0x1)<<1 );	// Reset de counters ON.	OKAY
	T0MCR &= ~( (0x1)<<2 );	// Stop timer OFF.			OKAY

	// Sacar el timer del estado RESET y habilitarlo para contar lo hago desde
	// la función Sampling_Start(), cuando sea necesario.
}


void ADC_Timer0_Config(uint16_t s_rate){
	double microseg = (double)1/(double)1000000;
	double Ts=0;
	uint32_t match=0;

	fmuestreo = s_rate;
    	Ts = (double)1 / (double)fmuestreo ;

	// 1. Prescale Counter. El timer hará (T0PR+1) ciclos de su clock (CCLK/4) hasta hacer Timer Count + 1.
	// Con este valor, +1 Timer Counter es un ciclo de 1 microseg.
	T0PR = 24;

	match = (uint32_t) ( Ts / microseg )  ;

	// 2. Timer Match. Valor hasta el que cuenta el timer.
	// Por default, sample_rate = 2.5kHz => match=400 useg hasta disparar una conversión
	// Con este valor, la frecuencia del timer es menor a la del adc. f = 2500 Hz
	T0MR0 = match;
}


uint32_t is_ADC_ON( void ){
	uint32_t read = T0TCR;
	read &= ( (0x1)<<0 );
	return read;
}


void ADC_Init(void){
	uint8_t Channel_Default;

	// 1. Alimentación del ADC.
	PCONP |= (0x01<<12);


	// 2. Habilitar el ADC.
	AD0CR |= (0x01<<21);

	// 3. PCLK del ADC.

//	PCLKSEL0 |= ( (0x1) << 24 );		// Bits 24:25 == 01 => CCLK/1 = 100 Mega
//	PCLKSEL0 &= ~ ( (0x1) << 25 );

	PCLKSEL0 &= ~(0x03<<24);			// Bits 24:25 == 00 => CCLK/4 = 25 Mega

//	PCLKSEL0 |= ( (0x3) << 24 );		// Bits 24:25 == 11 => CCLK/8 = 12.5 Mega


	// 4. Selecciono modo "Software Controlled". Bit 16 (BURST) ==  0.
	AD0CR &= ~( (0x1)<<16 );

	// 5. Apago la conversión. Bits 24:26 == 000
	AD0CR &= ~( (0x7)<<24 );

	// Configuración del canal de entrada. El default será el canal 2.
	Channel_Default = 2;
	ADC_InputSelect(Channel_Default);

	// 8. Habilito interrupción correspondiente al ADC en el NVIC.
	ISER0 |= (1<<22);

	// 9. Definir Sample Rate.

	/* En Software-Controlled mode, una conversión son 65 clocks.
	 *
	 * SAMPLE RATE = CLK_ADC / 65

	 *
	 * CLK_ADC = PCLK_ADC0 / (CLKDIV + 1)
	 *
	 * CLK_ADC debe ser menor o igual a 13 MHz

	 */

	/* CLKDIV son bits 8 a 15 en AD0CR */
	AD0CR &= ~( (0xFF) << 8 );	// Pongo ceros para resetear CLKDIV => CLKDIV = 0
	AD0CR |= ( (0x63) << 8 ) ;	// CLKDIV = 99

	/* Entonces: CLK_ADC = (100/4)*10^6 / (0+1) = 25 000 000
	 *

	 * conversion rate = 25 000 000 / 65 =~ 384,615 kHz
	 */
}


/* LAS SIGUIENTES FUNCIONES, TOCAN REGISTROS (SON DRIVERS !!). PERO SE LLAMAN DESDE LA MdE !!? */

void Start_Sampling( void ){
	// Saco el timer del estado RESET.
	T0TCR &= ~( (0x01)<<1 );		// OKAY
	// Arranco el timer.
	T0TCR |= ( (0x01)<<0 );			// OKAY
}

void Stop_Sampling( void ){
	// Detengo el timer.
	T0TCR &= ~( (0x01)<<0 );		// OKAY
	// Pongo el timer en estado RESET.
	T0TCR |= ( (0x1)<<1 );			// OKAY

	// En RESET ya se hace, pero por las dudas: pongo en 0 el timer counter y el prescale counter.
	T0TC = 0x0;
	T0PC = 0x0;

	// Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );			// OKAY
}
