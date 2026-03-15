#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(int p) : pin(p) {}

void LimitSwitch::begin() {
  pinMode(pin, INPUT_PULLUP);
}

bool LimitSwitch::isPressed() {
  return digitalRead(pin) == LOW;
}