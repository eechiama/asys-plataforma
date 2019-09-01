/*******************************************************************************************************************************//**
 *
 * @file		PR_UART_0.h
 * @brief		--Descripción del Módulo--
 * @date		Nov 12, 2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/


#ifndef PR_UART_0_H_
#define PR_UART_0_H_


/***********************************************************************************************************************************
 *** INCLUDES PÚBLICOS
 **********************************************************************************************************************************/


#include "DR_Tipos.h"
#include "DR_UART_0.h"


/***********************************************************************************************************************************
 *** DEFINES PÚBLICOS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PÚBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PÚBLICOS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PÚBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PÚBLICAS (PARA INCLUIR EN OTRO .C)
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES PÚBLICAS
 **********************************************************************************************************************************/


uint8_t U0_PushRx ( uint8_t data );
uint8_t U0_PopRx ( uint8_t *container );

uint8_t U0_PushTx ( uint8_t data );
uint8_t U0_PopTx ( uint8_t *container );


uint8_t Transmitir( void *data_vector, uint16_t size );


#endif /* PR_UART_0_H_ */