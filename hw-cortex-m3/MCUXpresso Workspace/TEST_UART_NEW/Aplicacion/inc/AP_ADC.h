/*******************************************************************************************************************************//**
 *
 * @file		AP_ADC.h
 * @brief		--Descripción del Módulo--
 * @date		04/11/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef INC_AP_ADC_H_
#define INC_AP_ADC_H_

/***********************************************************************************************************************************
 *** INCLUDES PÚBLICOS
 **********************************************************************************************************************************/


#include "PR_ADC.h"
#include "PR_UART_0.h"


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


void Preparar_y_Enviar( void );
void EnviarMuestra( uint16_t MuestraEfectiva );


#endif /* INC_AP_ADC_H_ */












