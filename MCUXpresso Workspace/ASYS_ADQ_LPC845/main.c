/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>

#include <HAL_SYSCON.h>

// Includes del LPC845
#include <AP_LEDS.h>
#include <AP_UART.h>
#include <AP_MSG_RX.h>
#include "../includes/AP_ADC.h"
#include "../includes/AP_ADQ_COMMANDS.h"		// debo revisar y colocarlo en carpeta portables
#include "../includes/AP_ADQ_SM.h"				// debo revisar y colocarlo en carpeta portables

#define MSG_MAX_LENGTH		COMMAND_MAX_LENGTH

unsigned char msg_buffer[MSG_MAX_LENGTH] = {0};

static const msg_rx_protocol_t protocol = {
	.symbol_msg_start = START_SYMBOL_COMMAND,
	.symbol_msg_end = END_SYMBOL,
	.msg_buffer = msg_buffer,
	.msg_max_length = MSG_MAX_LENGTH,
	.byte_receiver = wrapper_byteReceiver,
	.msg_reader = command_interpreter
};

int main(void) {

	// Initialize FRO clock @24MHz (no divisor)
	hal_syscon_fro_clock_config(1);

	// Set the FRO clock to be the main clock, without division.
	hal_syscon_system_clock_set_source(HAL_SYSCON_SYSTEM_CLOCK_SEL_FRO);
	hal_syscon_system_clock_set_divider(1);

	// Configure the FRG divider for accurate UART baudrate (115200)
	hal_syscon_frg_config(0, HAL_SYSCON_FRG_CLOCK_SEL_MAIN_CLOCK, 47);

	init_leds();
	init_uart();
	adc_init();

    while(1) {
    	RX_Messages_SM(&protocol);
    	ADQ_SM();
    }

    return 0 ;
}
