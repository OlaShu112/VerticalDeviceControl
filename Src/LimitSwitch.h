#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

#include <Arduino.h>

class LimitSwitch {
  int pin;

public:
  LimitSwitch(int p);
  void begin();
  bool isPressed();
};

#endif