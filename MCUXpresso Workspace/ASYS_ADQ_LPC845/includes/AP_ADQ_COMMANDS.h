/**
 * @file	AP_ADQ_COMMANDS.h
 * @brief	x
 * @author	Esteban E. Chiama
 * @date	Aug 14, 2020
 * @version	1.0
 */

#ifndef AP_ADQ_COMMANDS_H_
#define AP_ADQ_COMMANDS_H_

#include <AP_GENERATOR.h>

#define COMMAND_MAX_LENGTH		7

#define START_SYMBOL_COMMAND	'$'
#define START_SYMBOL_DATA		'%'
#define	END_SYMBOL				'#'

typedef enum {
	NO_COMMAND = 0,
	ADC_START,
	ADC_STOP,
	CONFIG_SR,
	CONFIG_INPUT,
	SEND_TEST_SIGNAL_1,
	SEND_TEST_SIGNAL_2,
	GENERATOR_START,
	GENERATOR_STOP
} commands_en;

extern volatile commands_en command;

extern volatile unsigned short int rx_sampleRate;

extern volatile unsigned char rx_channel;

extern volatile unsigned short int rx_divider;

extern volatile signal_sel_en rx_waveform;

/**
 * @brief		Reads character array 'word' and tries to decipher any incoming commands.
 * 				If a command is found, it's set onto the global variable 'command'.
 */
void command_interpreter( const unsigned char word[] );

#endif /* AP_ADQ_COMMANDS_H_ */
