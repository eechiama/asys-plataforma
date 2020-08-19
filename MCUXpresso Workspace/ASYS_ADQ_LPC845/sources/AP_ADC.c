/**
 * @file	AP_ADC.c
 * @brief	x
 * @author	Esteban E. Chiama
 * @date	Apr 8, 2020
 * @version	1.0
 */

/*
 * Asumiendo que el LPC845 está corriendo con el FRO como system clock a 24MHz
 * Quiero default SAMPLE RATE para el ADQ de 2.5kHz
 * (ADC configurado con conversiones disparadas por hardware trigger en flanco ascendente de ctimer match 3)
 *
 * CTIMER con PRESCALER = 0 entonces también corre a 24MHz
 * Match value es 4800 => 24e6/4800 = 5kHz
 * Tendré flanco ascendente con frecuencia 2.5kHz
 */

// ===================================
//	Includes
// ===================================

#include "../includes/AP_ADC.h"

#include <HAL_ADC.h>
#include <HAL_CTIMER.h>
#include <stddef.h>

// ===================================
//	Private function headers
// ===================================

static void adc_callback(void);

// ===================================
//	Private constants
// ===================================

#define		ADC_SAMPLE_RATE		480e3
#define		ADC_SEQUENCE		HAL_ADC_SEQUENCE_SEL_A

#define		CTIMER_PRESCALER	0

#define		DEFAULT_CTIMER_MATCH_FREQ			(DEFAULT_SAMPLING_RATE * 2)
#define		DEFAULT_CTIMER_MATCH_FREQ_USEG		( (1/((float)DEFAULT_CTIMER_MATCH_FREQ)) / (float)1e-6 )

// ===================================
//	Private datatypes
// ===================================

// ===================================
//	Private tables
// ===================================

// ===================================
//	Shared global variables
// ===================================

volatile char flag_adc_samples_ready = 0;

// ===================================
//	Private global variables
// ===================================

static hal_adc_sequence_config_t adc_config =
{
	.channels = (1 << DEFAULT_ADC_CHANNEL),
	.trigger = HAL_ADC_TRIGGER_SEL_T0_MAT3,
	.trigger_pol = HAL_ADC_TRIGGER_POL_SEL_POSITIVE_EDGE,
	.sync_bypass = HAL_ADC_SYNC_SEL_ENABLE_SYNC,
	.mode = HAL_ADC_INTERRUPT_MODE_EOC,
	.burst = 0,
	.single_step = 1,
	.low_priority = 0,
	.callback = adc_callback
};

static hal_ctimer_match_config_t timer_match_config = {
	.interrupt_on_match = 0,
	.reset_on_match = 1,
	.stop_on_match = 0,
	.reload_on_match = 0,
	.match_value_useg = DEFAULT_CTIMER_MATCH_FREQ_USEG,
	.match_action = HAL_CTIMER_MATCH_TOGGLE_PIN,
	.enable_external_pin = 0,
	.match_pin = HAL_GPIO_PORTPIN_0_1,
	.callback = NULL
};

static uint32_t	ctimer_match_freq = DEFAULT_SAMPLING_RATE;

static volatile uint16_t adc_sample = 0;

static uint32_t samples_buffer_length = 1;
static volatile uint16_t *samples_buffer = &adc_sample;
static volatile uint32_t inx_samples = 0;

// ===================================
//	Private functions
// ===================================

static void adc_callback(void)
{
	hal_adc_sequence_result_t adc_result;

	if(hal_adc_sequence_get_result(ADC_SEQUENCE, &adc_result) == HAL_ADC_SEQUENCE_RESULT_VALID)
	{
		samples_buffer[inx_samples] = adc_result.result;
		inx_samples++;
		inx_samples %= samples_buffer_length;

		if( !inx_samples ) flag_adc_samples_ready = 1;
	}
}

// ===================================
//	Public functions
// ===================================

void adc_init(void){
	hal_adc_init_sync_mode(ADC_SAMPLE_RATE, HAL_ADC_LOW_POWER_MODE_DISABLED);
	hal_adc_sequence_config(ADC_SEQUENCE, &adc_config);

	hal_ctimer_timer_mode_init(CTIMER_PRESCALER);
	hal_ctimer_timer_mode_match_config(HAL_CTIMER_MATCH_3, &timer_match_config);
}

void adc_start(void){
	hal_adc_sequence_start(ADC_SEQUENCE);
	hal_ctimer_timer_mode_start();
}

void adc_stop(){
	hal_ctimer_timer_mode_stop();
	hal_ctimer_timer_mode_reset();

	hal_adc_sequence_stop(HAL_ADC_SEQUENCE_SEL_A);

	// make trigger signal inactive, as defined by TRIGPOL bit,
	// so that when enabling there wont be a spurious hardware trigger.
	hal_ctimer_match_clear_output(HAL_CTIMER_MATCH_3);
}

void adc_set_sample_rate(unsigned int sample_rate){
	float sample_rate_usegs;

	// Because of toggling signal trigger, we need double the ctimer frequency asked
	sample_rate *= 2;
	sample_rate_usegs = 1/(float)sample_rate;
	sample_rate_usegs = sample_rate_usegs / (float)1e-6;

	hal_ctimer_timer_mode_match_change_value(HAL_CTIMER_MATCH_3, sample_rate_usegs);
	ctimer_match_freq = sample_rate;
}

// esta función se llama solamente luego de haber hecho adc_stop()
// para modificar channels se necesita la secuencia deshabilitada.
void adc_set_channel(char channel){
	adc_config.channels = 0;
	adc_config.channels = (1 << channel);
	hal_adc_sequence_config(ADC_SEQUENCE, &adc_config);
}

void adc_sample_buffer_config(unsigned short int *buffer, unsigned int length){
	samples_buffer = buffer;
	samples_buffer_length = length;
	inx_samples = 0;
}
