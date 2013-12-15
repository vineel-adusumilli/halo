#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include "main.h"
#include "adc.h"
#include "pwm.h"

#define F_CPU 16000000UL // 16 MHz

#define PI 3.14159265

// Operation modes
#define COLOR_MODE   0
#define TEMP_MODE    1
#define RAINBOW_MODE 2

int main(void) {
  adc_init();
  pwm_init();

  pwm_set_r(0);
  pwm_set_g(0);
  pwm_set_b(0);
  
  uint8_t mode = COLOR_MODE;
  uint8_t brightness, temperature, r, g, b;
  int t = 0;
  for (;;) {
    switch (mode) {
      case COLOR_MODE:
        pwm_set_r(adc_read(0));
        pwm_set_g(adc_read(1));
        pwm_set_b(adc_read(2));
        break;
      case TEMP_MODE:
        brightness = adc_read(0);
        temperature = adc_read(1);

        // Color temperature calculation loosely based on http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
        if (temperature < 155) {
          r = 255;
          g = 101 + temperature;
        } else {
          r = 332 - temperature / 2;
          g = 410 - temperature;
        }
        if (temperature < 160) {
          b = (uint8_t) (8 * temperature / 5.0);
        } else {
          b = 255;
        }
        pwm_set_r((uint8_t) (r * brightness / 255.0));
        pwm_set_g((uint8_t) (g * brightness / 255.0));
        pwm_set_b((uint8_t) (b * brightness / 255.0));
        break;
      case RAINBOW_MODE:
        brightness = adc_read(0);
        pwm_set_r((uint8_t) ((127 * cos(PI * t / 600.0) + 128)));
        pwm_set_g((uint8_t) ((127 * cos(PI * (t + 400) / 600.0) + 128)));
        pwm_set_b((uint8_t) ((127 * cos(PI * (t + 800) / 600.0) + 128)));
        t++;
        _delay_ms(10);
        break;
    }
  }
  
  return 0;
}
