/*
 * AP_GENERATOR.c
 *
 *  Created on: Nov 16, 2020
 *      Author: stv
 */
// reminder: WKT frequency generated from FRO is 750kHz.
// reminder: DACOUT1	PIO0_29

#include <stddef.h>	// NULL definition
#include <HAL_DAC.h>
#include <HAL_WKT.h>
#include <AP_GENERATOR.h>

#define	DAC_CHANNEL					(HAL_DAC_SEL_1)
#define DAC_INIT_VALUE				511

// (750kHz/6) = 125kHz frequency of analog value update.	(8 useg)
// (750kHz/12) = 62.5kHz frequency of analog value update.	(16 useg)
#define WKT_RELOAD_VALUE			12

#define	WAVEFORM_SAMPLED_POINTS		125

// LUT sine signal, 125 puntos
static const uint16_t sine[WAVEFORM_SAMPLED_POINTS] = {
512,537,563,589,614,640,665,689,713,737,
760,782,804,825,845,864,882,900,916,931,
946,959,971,982,991,1000,1007,1013,1017,1020,
1022,1023,1022,1020,1017,1013,1007,1000,991,982,
971,959,946,931,916,900,882,864,845,825,
804,782,760,737,713,689,665,640,614,589,
563,537,512,486,460,434,409,383,358,334,
310,286,263,241,219,198,178,159,141,123,
107,92,77,64,52,41,32,23,16,10,
6,3,1,0,1,3,6,10,16,23,
32,41,52,64,77,92,107,123,141,159,
178,198,219,241,263,286,310,334,358,383,
409,434,460,486,511
};

// LUT ramp signal, 125 puntos
static const uint16_t ramp[WAVEFORM_SAMPLED_POINTS] = {
0,8,16,25,33,41,49,57,65,74,
82,90,98,106,115,123,131,139,147,155,
164,172,180,188,196,205,213,221,229,237,
246,254,262,270,278,286,295,303,311,319,
327,336,344,352,360,368,376,385,393,401,
409,417,426,434,442,450,458,466,475,483,
491,499,507,516,524,532,540,548,557,565,
573,581,589,597,606,614,622,630,638,647,
655,663,671,679,687,696,704,712,720,728,
737,745,753,761,769,777,786,794,802,810,
818,827,835,843,851,859,868,876,884,892,
900,908,917,925,933,941,949,958,966,974,
982,990,998,1007,1015
};

// LUT square signal, 125 puntos
static const uint16_t square[WAVEFORM_SAMPLED_POINTS] = {
1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,
1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,
1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,
1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,
1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,
1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,
1023,1023,1023,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0
};

static const uint16_t * waveform_tables[SIGNALS_AMOUNT] = {
	sine,
	ramp,
	square
};

static const uint8_t dividers[] = { 1, 2, 4, 5, 8, 10, 20, 25, 40, 50, 100 };	// son 11

static volatile uint8_t idx_LUT = 0;

static volatile uint8_t idx_wkt_timeout = 0;

static volatile signal_sel_en idx_waveform = SINEWAVE;

static const uint16_t * active_LUT = sine;

static volatile uint8_t freq_div = 1;

/**
 * @brief		Callback utilizado para actualizar el valor del DAC cuando vence el WKT.
 */
static void wkt_callback(void);

static void wkt_callback(void){
	idx_wkt_timeout++;
	idx_wkt_timeout %= freq_div;
	if( !idx_wkt_timeout ) {
		idx_LUT++;
		idx_LUT %= WAVEFORM_SAMPLED_POINTS;
		hal_dac_update_value(DAC_CHANNEL, active_LUT[idx_LUT]);
	}
	hal_wkt_start_count_with_value(WKT_RELOAD_VALUE);
}

void generator_init(){
	hal_wkt_init(HAL_WKT_CLOCK_SOURCE_FRO_DIV, 0, wkt_callback);
	hal_dac_init(DAC_CHANNEL, HAL_DAC_SETTLING_TIME_1US_MAX, DAC_INIT_VALUE);
}

void generator_config(signal_sel_en signal_select, freq_div_sel_en div_select){
	idx_waveform = signal_select;
	active_LUT = waveform_tables[idx_waveform];
	freq_div = dividers[div_select];
}

void generator_start(){
	idx_LUT = 0;
	idx_wkt_timeout = 0;
	hal_dac_update_value(DAC_CHANNEL, active_LUT[idx_LUT]);
	hal_wkt_start_count_with_value(WKT_RELOAD_VALUE);
	return;
}

void generator_stop(){
	hal_wkt_register_callback(NULL);
	hal_wkt_stop_count();
	hal_dac_update_value(DAC_CHANNEL, DAC_INIT_VALUE);
}
