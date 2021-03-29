/*
 * AP_DEBUG.h
 *
 *  Created on: Nov 17, 2020
 *      Author: stv
 */

#ifndef AP_DEBUG_H_
#define AP_DEBUG_H_

#define 	DEBUG_MSG_LENGTH	4

typedef enum{
	RX_MESSAGES_SM = 0,
	GENERATOR_SM,
	DEBUG_LISTS_AMOUNT
} code_list_sel_en;

typedef enum{
	RX_POP_TRUE = 0,
	RX_BEGAN_WORD,
	RX_OVERFLOW,
	RX_END_WORD,
	GEN_RESET,
	GEN_START,
	GEN_STOP,
	GEN_COUNT
} code_sel_en;

void debug_tx_msg(code_list_sel_en, code_sel_en);

#endif /* AP_DEBUG_H_ */
