#include "Clip.h"

Clip::Clip(int p) : pin(p) {}

void Clip::begin() {
  pinMode(pin, OUTPUT);
}

void Clip::release() {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
}