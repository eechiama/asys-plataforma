/*
 * AP_GENERATOR_SM.c
 *
 *  Created on: Nov 16, 2020
 *      Author: stv
 */

#include <AP_GENERATOR_SM.h>
#include <AP_GENERATOR.h>
#include <AP_ADQ_COMMANDS.h>
#include <AP_DEBUG.h>

typedef enum {
	GENERATOR_RESET = 0,
	GENERATOR_WAITING,
	GENERATOR_ACTIVE
} states_en;

void Generator_SM(){
  static states_en generator_state = GENERATOR_WAITING;
  static unsigned char f_gen_stopped = 0;
  static unsigned int count = 0;

  switch( generator_state ){

    case GENERATOR_RESET:

    	generator_stop();
    	generator_state = GENERATOR_WAITING;

    	break;

    case GENERATOR_WAITING:

    	if( f_gen_stopped ){
    		count++;
    		count %= 5000;
    		if( !count ){
    			debug_tx_msg(GENERATOR_SM, GEN_COUNT);
    			f_gen_stopped = 0;
    		}
    	}

    	if( command == GENERATOR_START ){
			command = NO_COMMAND;
			generator_config( rx_waveform, FREQ_DIV_1 );
			generator_start();
			generator_state = GENERATOR_ACTIVE;
			debug_tx_msg(GENERATOR_SM, GEN_START);
		}

    	break;

    case GENERATOR_ACTIVE:

		if( command == GENERATOR_STOP ){
			command = NO_COMMAND;
			generator_stop();
			f_gen_stopped = 1;
			generator_state = GENERATOR_WAITING;
			debug_tx_msg(GENERATOR_SM, GEN_STOP);
		}

		break;

    default:
    	generator_state = GENERATOR_RESET;
    	break;
  }
}
