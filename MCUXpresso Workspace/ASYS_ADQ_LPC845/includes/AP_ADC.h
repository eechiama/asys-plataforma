/**
 * @file	AP_ADC.h
 * @brief	x
 * @author	Esteban E. Chiama
 * @date	Apr 8, 2020
 * @version	1.0
 */

#ifndef AP_ADC_H_
#define AP_ADC_H_

// ===================================
//	Includes
// ===================================

// ===================================
//	Constants
// ===================================

// Default initialization values
// MATLAB GUI default values should be coherent with these settings
#define		DEFAULT_ADC_CHANNEL					0
#define		DEFAULT_SAMPLING_RATE				2500

// ===================================
//	Datatypes
// ===================================

// ===================================
//	Tables
// ===================================

// ===================================
//	Shared global variables
// ===================================

extern volatile char flag_adc_samples_ready;

// ===================================
//	Function headers
// ===================================

void adc_init(void);

void adc_start(void);

void adc_stop(void);

void adc_set_sample_rate(unsigned int sample_rate);

void adc_set_channel(char channel);

void adc_sample_buffer_config(unsigned short int *buffer, unsigned int length);

#endif /* AP_ADC_H_ */
