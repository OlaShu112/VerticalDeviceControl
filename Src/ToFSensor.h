/*
#ifndef TOFSENSOR_H
#define TOFSENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>

class ToFSensor {
  VL53L1X tof;

public:
  void begin();
  float distanceMeters();
};

#endif
*/

#ifndef TOFSENSOR_H
#define TOFSENSOR_H

class ToFSensor {
public:
    void begin();
    float distanceMeters();
};

#endif