/*******************************************************************************************************************************//**
 *
 * @file		AP_ADQ_SM.c
 * @brief		--Descripción del Módulo--
 * @date		20/03/2018
 * @author		Esteban E. Chiama
 *
 **********************************************************************************************************************************/

#include <AP_ADQ_SM.h>

#include <AP_LEDS.h>
#include <AP_UART.h>

// Portables
#include <AP_ADC.h>
#include <AP_ADQ_COMMANDS.h>

#define SIZE_SIGNAL_1	200
#define SIZE_SIGNAL_2	85

#define	TEST_SIGAL_PKG_SIZE	3
#define	ADC_DATA_PKG_SIZE	4

#define	ADC_SAMPLES_BUFFER_LENGTH	1

typedef enum {
	ADQ_RESET,
	ADQ_IDLE,
	ADQ_ACTIVE,
	ADQ_TEST_SIGNAL
}states_en;

typedef enum {
	TX_DOING,
	TX_DONE
}tx_test_status_en;

typedef enum {
	SELECT_SIGNAL_1,
	SELECT_SIGNAL_2
}signal_select_en;

static const unsigned char test_signal_1[] = {
	90, 95, 124, 153, 182, 211, 241, 230, 202, 173,
	143, 114, 89, 83, 75, 67, 70, 78, 85, 90,
	90, 90, 90, 90, 92, 100, 107, 113, 118, 122,
	124, 125, 124, 121, 117, 111, 104, 97, 90, 90,
	90, 90, 90, 90, 90, 90, 90, 90, 92, 93,
	93, 92, 90, 90, 90, 90, 90, 90, 90, 90,
	90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
	97, 104, 109, 112, 113, 111, 107, 100, 91, 90,
	90, 90, 90, 90, 90, 90, 95, 124, 153, 182,
	211, 241, 230, 202, 173, 143, 114, 89, 83, 75,
	67, 70, 78, 85, 90, 90, 90, 90, 90, 92,
	100, 107, 113, 118, 122, 124, 125, 124, 121, 117,
	111, 104, 97, 90, 90, 90, 90, 90, 90, 90,
	90, 90, 90, 92, 93, 93, 92, 90, 90, 90,
	90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
	90, 90, 90, 90, 90, 97, 104, 109, 112, 113,
	111, 107, 100, 91, 90, 90, 90, 90, 90, 90,
	90, 95, 124, 153, 182, 211, 241, 230, 202, 173,
	143, 114, 89, 83, 75, 67, 70, 78, 85, 90,
	90, 90, 90, 90, 92, 100, 107, 113, 118, 122
};

static const unsigned char test_signal_2[] = {
	94, 95, 128, 158, 187, 215, 245, 233, 202, 174,
	144, 114, 94, 84, 77, 69, 72, 81, 85, 94,
	93, 94, 92,  92,  92, 101, 110, 115, 123, 123,
	129, 128, 127, 126, 118, 113, 107, 101, 94, 90,
	91, 92, 90, 93, 92, 91, 91, 94, 95, 96,
	98, 93, 94, 94, 93, 91, 93, 91, 91, 91,
	94, 90, 91, 90, 92, 90, 94, 91, 90, 91,
	99, 104, 114, 114, 114, 112, 108, 100, 94, 94,
	93, 90, 90, 94, 94
};

static const unsigned char test_signal_sizes[] = {
	SIZE_SIGNAL_1,
	SIZE_SIGNAL_2
};

static const unsigned char * const ptr_signal_tables[] = {
	(void *)&test_signal_1,
	(void *)&test_signal_2
};

static volatile unsigned short int adc_samples[ADC_SAMPLES_BUFFER_LENGTH] = {0};

static unsigned int inx_samples = 0;

static char flag_sending = 0;

/**
 * @brief		Takes a sample and makes a data package according to the communication protocol.
 * 				This package is then queued up for transmission by UART.
 *
 * @return		Returns a value informing operation success or failure,
 * 				the same value returned by TransmitBytes.
 */
static transmit_bytes_result_en TransmitSample( unsigned short int samp );

/**
 * @brief		Selects a test signal from the internal test signal tables according to parameter 'signal_choice'.
 * 				Starts transmission of the test signal samples, packaged according to protocol.
 * 				On every call to this function a single sample is queued for transmission, until the end of the
 * 				selected signal table is reached.
 */
static tx_test_status_en tx_test_signal( signal_select_en signal_choice );

static transmit_bytes_result_en TransmitSample( unsigned short int samp ) {
	unsigned char adc_data_pkg[ADC_DATA_PKG_SIZE];

	// ADC data 12 bit long, the 4 MSB are placed first on the message.
	adc_data_pkg[0] = START_SYMBOL_DATA;
	adc_data_pkg[1] = (unsigned char)((samp>>8) & 0xF);
	adc_data_pkg[2] = (unsigned char)(samp & 0xFF);
	adc_data_pkg[ADC_DATA_PKG_SIZE-1] = END_SYMBOL;

	return TransmitBytes(adc_data_pkg, ADC_DATA_PKG_SIZE);
}

static tx_test_status_en tx_test_signal( signal_select_en signal_choice ){
	static unsigned char inx = 0;
	unsigned char test_signal_pkg[TEST_SIGAL_PKG_SIZE];
//	unsigned int i = 0;

//	// delay
//	i=0;
//	while (i<10000){
//		i++;
//	}

	test_signal_pkg[0] = START_SYMBOL_DATA;
	test_signal_pkg[1] = *( ptr_signal_tables[signal_choice] + inx );
	test_signal_pkg[TEST_SIGAL_PKG_SIZE-1] = END_SYMBOL;
	
	if( TransmitBytes(test_signal_pkg, TEST_SIGAL_PKG_SIZE) ){
		inx++;
		inx %= test_signal_sizes[signal_choice];
	}

	if ( inx == 0 ){
		return TX_DONE;
	}

	return TX_DOING;
}

void ADQ_SM(void) {

	static tx_test_status_en	tx_signal_status = TX_DONE;
	static  signal_select_en	signal_selection = SELECT_SIGNAL_1;

	static states_en state = ADQ_RESET;

	switch (state) {

		case ADQ_RESET:
			state = ADQ_IDLE;
			adc_stop();
			leds_off();
			set_led(LED_GREEN);
			break;

		case ADQ_IDLE:

			if ( command == ADC_START && tx_signal_status == TX_DONE) {
				command = NO_COMMAND;
				state = ADQ_ACTIVE;
				flag_sending = 0;
				inx_samples = 0;
				adc_sample_buffer_config((unsigned short int *)adc_samples, ADC_SAMPLES_BUFFER_LENGTH);
				adc_start();
				clear_led(LED_GREEN);
				set_led(LED_BLUE);
			}

			if( command == CONFIG_SR ){
				command = NO_COMMAND;
				adc_set_sample_rate(rx_sampleRate);
			}

			if( command == CONFIG_INPUT ){
				command = NO_COMMAND;
				adc_set_channel(rx_channel);
			}

			if( command == SEND_TEST_SIGNAL_1 ){
				command = NO_COMMAND;
				state = ADQ_TEST_SIGNAL;
				signal_selection = SELECT_SIGNAL_1;
			}

			if( command == SEND_TEST_SIGNAL_2 ){
				command = NO_COMMAND;
				state = ADQ_TEST_SIGNAL;
				signal_selection = SELECT_SIGNAL_2;
			}
			break;

		case ADQ_TEST_SIGNAL:

			tx_signal_status = tx_test_signal(signal_selection);
			if ( tx_signal_status == TX_DONE ){
				command = NO_COMMAND;
				state = ADQ_IDLE;
			}
			break;

		case ADQ_ACTIVE:

			// When there's a sample ready, send by UART
			if (flag_adc_samples_ready) {
				flag_adc_samples_ready = 0;
				flag_sending = 1;
				inx_samples = 0;
			}

			if( flag_sending ){
				if( TransmitSample( adc_samples[inx_samples] ) ){
					inx_samples++;
					inx_samples %= ADC_SAMPLES_BUFFER_LENGTH;
					if( !inx_samples ){
						flag_sending = 0;
					}
				}
			}

			if ( command == ADC_STOP ) {
				command = NO_COMMAND;
				state = ADQ_IDLE;
				adc_stop();
				clear_led(LED_BLUE);
				set_led(LED_GREEN);
			}
			break;
	}
}
