/**
 * @file	AP_ADC.h
 * @brief	x
 * @author	Esteban E. Chiama
 * @date	Apr 8, 2020
 * @version	1.0
 */

#ifndef AP_ADC_H_
#define AP_ADC_H_

// Default initialization values
// MATLAB GUI default values should be coherent with these settings
#define		DEFAULT_ADC_CHANNEL					0
#define		DEFAULT_SAMPLING_RATE				2500

extern volatile char flag_adc_samples_ready;

/**
 * @brief		a
 */
void adc_init(void);

/**
 * @brief		a
 */
void adc_start(void);

/**
 * @brief		a
 */
void adc_stop(void);

/**
 * @brief		a
 */
void adc_set_sample_rate(unsigned int sample_rate);

/**
 * @brief		a
 */
void adc_set_channel(char channel);

/**
 * @brief		a
 */
void adc_sample_buffer_config(unsigned short int *buffer, unsigned int length);

#endif /* AP_ADC_H_ */
