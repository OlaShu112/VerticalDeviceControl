#ifndef INDICATOR_H
#define INDICATOR_H

#include <Arduino.h>

class Indicator {
  int pin;

public:
  Indicator(int p);
  void begin();
  void on();
  void off();
};

#endif