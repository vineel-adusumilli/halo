#include <avr/io.h>

#include "pwm.h"

void pwm_init(void) {
  // Set PD6/OC0A as output
  DDRD |= (1 << PD6);
  // Set PB1/OC1A as output
  DDRB |= (1 << PB1);
  // Set PD3/OC2B as output
  DDRD |= (1 << PD3);
  // Set Fast PWM mode on Timer 0
  TCCR0A |= (1 << WGM01) | (1 << WGM00);
  // Set Fast PWM 8-bit mode on Timer 1
  TCCR1A |= (1 << WGM10);
  TCCR1B |= (1 << WGM12);
  // Set Fast PWM mode on Timer 2
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  // Set non-inverting PWM on OC0A
  TCCR0A |= (1 << COM0A1);
  // Set non-inverting PWM on OC1A
  TCCR1A |= (1 << COM1A1);
  // Set non-inverting PWM on OC2B
  TCCR2A |= (1 << COM2B1);
  // Start Timer 0 with no prescaling
  TCCR0B |= (1 << CS00);
  // Start Timer 1 with no prescaling
  TCCR1B |= (1 << CS10);
  // Start Timer 2 with no prescaling
  TCCR2B |= (1 << CS20);
}

inline void pwm_set_r(uint8_t value) {
  OCR0A = value;
}

inline void pwm_set_g(uint8_t value) {
  OCR1AL = value;
}

inline void pwm_set_b(uint8_t value) {
  OCR2B = value;
}

