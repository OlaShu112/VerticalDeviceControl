#include "Motor.h"

Motor::Motor(int directionPin, int enablePin) : dirPin(directionPin), enPin(enablePin) {}

void Motor::begin() {
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  stop();
}

void Motor::up() {
  digitalWrite(dirPin, HIGH);
  digitalWrite(enPin, HIGH);
}

void Motor::down() {
  digitalWrite(dirPin, LOW);
  digitalWrite(enPin, HIGH);
}

void Motor::stop() {
  digitalWrite(enPin, LOW);
}