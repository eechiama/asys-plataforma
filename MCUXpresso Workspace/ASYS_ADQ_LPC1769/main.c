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

#include <AP_Adquisidor_MDE.h>
#include "DR_Init.h"

int main(void) {

	Kit_Init();

    while(1) {
    	RX_Mensajes();
    	MDE_Adquisidor();
    }

    return 0 ;
}
