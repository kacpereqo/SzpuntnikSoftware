#pragma once

#include <LIS3MDL.h>
#include <LSM6.h>

inline LSM6 &getLSM6() {
  static LSM6 imu;
  return imu;
}

inline LIS3MDL &getLIS3MDL() {
  static LIS3MDL mag;
  return mag;
}
