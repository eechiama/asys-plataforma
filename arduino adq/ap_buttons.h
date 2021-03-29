#ifndef AP_BUTTONS_H
#define AP_BUTTONS_H

// estado_buttonSM
const uint8_t NO_STATE = 0;

const uint8_t BUTTONS_INACTIVE = 1;

const uint8_t BUTTONS_ACTIVE = 2;


void Buttons( uint8_t *inform_status );

#endif /* AP_BUTTONS_H */
