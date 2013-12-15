#include <avr/io.h>

#include "adc.h"

// Initialize the ADC and justify output for 8-bit mode
void adc_init(void) {
  // Set ADC Prescaler to 128
  // ADC frequency will be 16 MHz/128 = 125 KHz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS2) | (1 < ADPS0);
  // Set reference voltage to AVcc
  ADMUX |= (1 << REFS0);
  // Reduce measurement to 8 bits in ADCH
  ADMUX |= (1 << ADLAR);
  // Enable ADC
  ADCSRA |= (1 << ADEN);
}

// Read from the ADC multiplexer
uint8_t adc_read(uint8_t channel) {
  // Clear old channel 
  ADMUX &= 0xF0;
  // Select channel
  ADMUX |= channel;
  // Start a new conversion
  ADCSRA |= (1 << ADSC);
  // Wait for conversion to finish
  while (ADCSRA & (1 << ADSC));
  // Return result
  return ADCH;
}


