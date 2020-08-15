/* ========= include files =========== */
/* =================================== */
#include "ap_filtro.h"

/* ======== private constants ======== */
/* =================================== */

/* ======== private datatypes ======== */
/* =================================== */

/* ==== private global variables ===== */
/* =================================== */
volatile uint16_t bufValues[BUFSIZE];
static uint8_t inxbuf = 0;

/* ==== shared global variables ====== */
/* =================================== */

/* ======= private prototypes ======== */
/* =================================== */

void bubble(volatile uint16_t *vector, int sizze);

/* ======= private functions ========= */
/* =================================== */

/* Funcion bubble, que ordena un vector de menor a mayor con el metodo de burbujeo.*/
void bubble(volatile uint16_t *vector, int sizze) {

  int aux; //para el swap.
  int i, j;

  for(j=0; j<sizze-1; j++) {

    for(i=0; i<sizze-1-j; i++) {

      if(vector[i]>vector[i+1]) {
        aux = vector[i+1];
        vector[i+1] = vector[i];
        vector[i] = aux;
      }
    }
  }
}

/* ======== public functions ========= */
/* =================================== */

// colocar una valor en el buffer
uint8_t queue_in_buffer( uint16_t val ){
  bufValues[inxbuf] = val;
  inxbuf++;
  
  inxbuf %= BUFSIZE;
  if( inxbuf == 0 ) return BUFFER_COMPLETED;
  
  return false;
}

// Función para volver a escribir en el buffer desde la posición 0.
void buffer_reset( void ){
  inxbuf = 0;
}

// Función para obtener la mediana del buffer.
uint16_t filtro_mediana( void ){
  uint16_t filteredVal;
  
  // Ordenamos el vector
  bubble(bufValues, BUFSIZE);

  // Calculamos la media
  filteredVal = ( bufValues[(BUFSIZE-1)/2] + bufValues[BUFSIZE/2] ) / 2;
  return filteredVal;
}
