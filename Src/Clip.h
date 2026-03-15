#ifndef CLIP_H
#define CLIP_H

#include <Arduino.h>

class Clip {
  int pin;

public:
  Clip(int p);
  void begin();
  void release();
};

#endif