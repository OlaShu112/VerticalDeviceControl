/* #include "ToFSensor.h"

void ToFSensor::begin() {
  Wire.begin();
  tof.init();
  tof.setDistanceMode(VL53L1X::Long);
  tof.setMeasurementTimingBudget(50000);
  tof.startContinuous(50);
}

float ToFSensor::distanceMeters() {
  tof.read();
  return tof.ranging_data.range_mm / 1000.0;
}
  */

// ToFSensor.cpp
#include "ToFSensor.h"

float testDistance = 2.2;

void ToFSensor::begin() {
    // nothing to initialize
}

float ToFSensor::distanceMeters() {
    testDistance -= 0.01;           // simulate platform moving up
    if (testDistance < 1.0) testDistance = 2.2;  // reset
    return testDistance;
}