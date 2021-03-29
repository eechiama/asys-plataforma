/*
 * AP_DEBUG.c
 *
 *  Created on: Nov 17, 2020
 *      Author: stv
 */

#include <AP_DEBUG.h>
#include <AP_UART.h>

static const char * code_list_RX_Messages_SM[4] = {
	"@rP\n",
	"@rB\n",
	"@rO\n",
	"@rE\n"
};

static const char * code_list_Generator_SM[4] = {
	"@gR\n",
	"@g1\n",
	"@g0\n",
	"@gC\n"
};

static const char ** debug_msg_lists[DEBUG_LISTS_AMOUNT] = {
		code_list_RX_Messages_SM,
		code_list_Generator_SM
};

void debug_tx_msg(code_list_sel_en idx_list, code_sel_en idx_code){

	unsigned short int substract = 0;

	switch(idx_list){
		case RX_MESSAGES_SM:	substract = 0; break;
		case GENERATOR_SM:		substract = 4; break;
		default:				break;
	}

	TransmitBytes( (unsigned char *) *(debug_msg_lists[idx_list] + idx_code - substract), DEBUG_MSG_LENGTH);
}


