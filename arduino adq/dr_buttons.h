#ifndef DR_BUTTONS_H
#define DR_BUTTONS_H

/* === public variables ==== */
/* ========================= */

extern volatile uint8_t sequence_enabled;

/* === public functions ==== */
/* ========================= */

void buttons_init(void);

void debounce(void);

void led_notification(void);

#endif /* DR_BUTTONS_H */
