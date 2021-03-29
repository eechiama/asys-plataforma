/*
 * AP_GENERATOR.h
 *
 *  Created on: Nov 16, 2020
 *      Author: stv
 */

#ifndef AP_GENERATOR_H_
#define AP_GENERATOR_H_

typedef enum {
	SINEWAVE = 0,
	RAMP,
	SQUARE,
	SIGNALS_AMOUNT
}signal_sel_en;

typedef enum {
	FREQ_DIV_1 = 0,
	FREQ_DIV_2,
	FREQ_DIV_4,
	FREQ_DIV_5,
	FREQ_DIV_8,
	FREQ_DIV_10,
	FREQ_DIV_20,
	FREQ_DIV_25,
	FREQ_DIV_40,
	FREQ_DIV_50,
	FREQ_DIV_100
}freq_div_sel_en;

extern volatile unsigned char flag_irq_timing;

/**
 * @brief		Inicializa los componentes utilizados por el generador de funciones.
 * 				WKT, DAC
 */
void generator_init(void);

/**
 * @brief		Comienza el generador de funciones utilizando el DAC1.
 */
void generator_start(void);

/**
 * @brief		Detiene el generador de funciones.
 */
void generator_stop(void);

/**
 * @brief		Configura la señal a generar y su divisor de frecuencia.
 * @param[in]	signal_select	Selección de la señal.
 * @param[in]	div_select		Selección del divisor de frecuencia.
 */
void generator_config(signal_sel_en signal_select, freq_div_sel_en div_select);

#endif /* AP_GENERATOR_H_ */
