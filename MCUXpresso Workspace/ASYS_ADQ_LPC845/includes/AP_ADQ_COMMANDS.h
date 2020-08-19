/**
 * @file	AP_ADQ_COMMANDS.h
 * @brief	x
 * @author	Esteban E. Chiama
 * @date	Aug 14, 2020
 * @version	1.0
 */

#ifndef AP_ADQ_COMMANDS_H_
#define AP_ADQ_COMMANDS_H_

// ===================================
//	Includes
// ===================================

// ===================================
//	Constants
// ===================================

#define COMMAND_MAX_LENGTH		7

#define START_SYMBOL_COMMAND	'$'
#define START_SYMBOL_DATA		'%'
#define	END_SYMBOL				'#'

// ===================================
//	Datatypes
// ===================================

typedef enum {
	NO_COMMAND = 0,
	START_ADC,
	STOP_ADC,
	CONFIG_SR,
	CONFIG_INPUT,
	SEND_TEST_SIGNAL_1,
	SEND_TEST_SIGNAL_2
} commands_en;

// ===================================
//	Tables
// ===================================

// ===================================
//	Shared global variables
// ===================================

extern volatile commands_en command;
extern volatile unsigned short int rx_sampleRate;
extern volatile unsigned char rx_channel;

// ===================================
//	Function headers
// ===================================

/**
 * @brief		Reads character array 'word' and tries to decipher any incoming commands.
 * 				If a command is found, it's set onto the global variable 'command'.
 */
void command_interpreter( const char word[] );

#endif /* AP_ADQ_COMMANDS_H_ */
