/*******************************************************************************************************************************//**
 *
 * @file		AP_ADQ_SM.h
 * @brief		--Descripción del Módulo--
 * @date		2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

#ifndef INC_AP_ADQ_SM_H
#define INC_AP_ADQ_SM_H

// ===================================
//	Includes
// ===================================

// ===================================
//	Constants
// ===================================

// ===================================
//	Datatypes
// ===================================

// ===================================
//	Tables
// ===================================

// ===================================
//	Shared global variables
// ===================================

// ===================================
//	Function headers
// ===================================

/**
 * @brief		ADQ state machine. Controls ADC configuration, operation and data transmission.
 * 				Also controls transmission of test signals.
 * 				Reads the global variable 'command' for instructions.
 */
void ADQ_SM(void);

#endif /* INC_AP_ADQ_SM_H */
