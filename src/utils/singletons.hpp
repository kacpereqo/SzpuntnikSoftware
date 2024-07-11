#pragma once

#include "Arduino.h"
#include <LIS3MDL.h>
#include <LSM6.h>

inline LSM6 &getLSM6() {
  static LSM6 imu;

  if (!imu.init()) {
    Serial.println("Failed to detect and initialize IMU!");
    while (1)
      ;
  }
  return imu;
}

inline LIS3MDL &getLIS3MDL() {
  static LIS3MDL mag;
  if (!mag.init()) {
    Serial.println("Failed to detect and initialize Magnetometer!");
    while (1)
      ;
  }
  return mag;
}
