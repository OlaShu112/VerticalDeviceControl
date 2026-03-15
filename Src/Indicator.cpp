#include "Indicator.h"

Indicator::Indicator(int p) : pin(p) {}

void Indicator::begin() {
  pinMode(pin, OUTPUT);
}

void Indicator::on() {
  digitalWrite(pin, HIGH);
}

void Indicator::off() {
  digitalWrite(pin, LOW);
}