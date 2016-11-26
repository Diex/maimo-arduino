#ifndef _INC_PISO
#define _INC_PISO
#endif
#include <Arduino.h>
#include "tables.h"

class Piso {
  unsigned int pwmpin;
  boolean batteryChanged;
  unsigned int state;
  static const unsigned int RUNNING = 4;
  static const unsigned int TOP = 5;
  static const unsigned int BOTTOM = 6;

  unsigned int brightness;
  unsigned int maxBrightness;
  float goalLimit;
  float btlLimit;

  unsigned int timer1;
  unsigned int delay1;

public:

  Piso() {};

  Piso(unsigned int pin) {
    pwmpin = pin;
    pinMode(pwmpin, OUTPUT);
    digitalWrite(pwmpin, 1);

    timer1 = 0;
    delay1 = 10;

    maxBrightness = 63;
    goalLimit = 0.70;    // 75 porciento de carga
    btlLimit = 0.05;      // la minima carga antes de bajar

    state = RUNNING;

    batteryChanged = false;
    brightness = 0;
    render();
  };

  int getBrightness() {
    return brightness;
  }

  // ---------------
  void setBrightness(unsigned int b) {
    brightness = b;
  }

  void render() {
    unsigned int dc = pgm_read_word(&(shades[brightness]));
    analogWrite(pwmpin, 255 - dc);
  }


  void blink(int del) {
    setBrightness(63);
    render();
    delay(del);

    setBrightness(0);
    render();
    delay(del);
  }

};



