/* ========= include files =========== */
/* =================================== */
#include <Arduino.h>
#include "dr_buttons.h"

/* ======== private constants ======== */
/* =================================== */
// pins
const int buttonPin = 2;
const int ledPin = 4;

// debounce accept state change condition
const int CHANGE_IS_STABLE = 10000;

// push buttons circuit logic (active high / active low)
const uint8_t PUSHED = HIGH;

/* ======== private datatypes ======== */
/* =================================== */

/* ==== private global variables ===== */
/* =================================== */
// for debounce
static int count_changes = 0;

// pushButton
volatile uint8_t currentState;

/* ==== shared global variables ====== */
/* =================================== */
volatile uint8_t sequence_enabled = 0;

/* ======= private prototypes ======== */
/* =================================== */

/* ======= private functions ========= */
/* =================================== */

/* ======== public functions ========= */
/* =================================== */

void buttons_init( void ){
  pinMode(buttonPin, INPUT);

  // led for the active button
  pinMode(ledPin, OUTPUT);

  currentState = digitalRead(buttonPin);
}

void debounce ( void ) {
  uint8_t change;
  uint8_t auxState = digitalRead(buttonPin);

  // Check for a state change
  change = ( currentState ^ auxState );

  if ( change ){
        count_changes = count_changes + 1;

        // if the change appears stable, toggle the currentState.
        if ( count_changes == CHANGE_IS_STABLE ){
          count_changes = 0;
          currentState = currentState ^ change;
        }
  }
  else {
    count_changes = 0;
  }
}

void led_notification( void ){
  if ( currentState == PUSHED ){
    digitalWrite(ledPin, HIGH);
    sequence_enabled = 1;
  }
  else{
    digitalWrite(ledPin, LOW);
    sequence_enabled = 0;
  }
}
