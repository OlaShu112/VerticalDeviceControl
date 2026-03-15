#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  int dirPin;
  int enPin;

public:
  Motor(int directionPin, int enablePin);
  void begin();
  void up();
  void down();
  void stop();
};

#endif