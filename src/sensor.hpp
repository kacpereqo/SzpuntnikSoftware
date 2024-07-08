#pragma once

#include "vec.hpp"
#include <cstdint>

class Sensor {
protected:
  uint8_t scale;
  uint8_t rate;
  float scale_factor;

public:
  virtual void configure() = 0;
  virtual void calibrate() = 0;

  virtual Vec3<float> &getData() = 0;
  virtual Vec3<int16_t> &getRawData() = 0;
};