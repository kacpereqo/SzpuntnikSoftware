#pragma once

#include "vec.hpp"
#include <cstdint>

class Sensor {
public:
  virtual void configure() = 0;
  virtual void calibrate() = 0;

  virtual Vec3<float> &getData() = 0;
  virtual Vec3<int16_t> &getRawData() = 0;
};