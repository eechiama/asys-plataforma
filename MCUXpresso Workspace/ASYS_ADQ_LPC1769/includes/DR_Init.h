/*
 * DR_Init.h
 *
 *  Created on:
 *  Author:
 */

#ifndef DR_INIT_H_
#define DR_INIT_H_

#include "Regs_LPC176x.h"
#include "DR_GPIO.h"
#include "DR_PINSEL.h"
#include "KitInfo2.h"

#include "DR_SysTick.h"
#include "DR_IO.h"
#include "FW_LCD.h"

#include "DR_UART_0.h"
#include "DR_ADC.h"


//Funciones de inicialización
void Kit_Init(void);
void PLL_Init(void);

#endif /* DR_INIT_H_ */
