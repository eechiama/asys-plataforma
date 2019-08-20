#ifndef AP_FILTRO_H
#define AP_FILTRO_H

/* ===== include files ===== */
/* ========================= */
#include <Arduino.h>

/* ======= constants ======= */
/* ========================= */
const int BUFSIZE = 10;
const int BUFFER_COMPLETED = 1;

//#define FILTRAR   1

/* ======= datatypes ======= */
/* ========================= */

/* === public variables ==== */
/* ========================= */

/* === public functions ==== */
/* ========================= */
uint8_t queue_in_buffer( uint16_t val );
void buffer_reset( void );
uint16_t filtro_mediana( void );

#endif /* AP_FILTRO_H */
