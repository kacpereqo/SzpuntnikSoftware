#pragma once

#include "sensor.hpp"
#include "vec.hpp"
#include <LIS3MDL.h>
#include <cstdint>

class Magnetometer : public Sensor {
private:
  Vec3<int16_t> max_values_raw;
  Vec3<int16_t> min_values_raw;

  Vec3<int16_t> raw;
  Vec3<float> data;
  LIS3MDL &sensor;

public:
  enum MagScale : uint8_t {
    gauss4,
    gauss8,
    gauss12,
    gauss16,
  };

  enum MagRate : uint8_t {
    Hz0_625,
    Hz1_25,
    Hz2_5,
    Hz5,
    Hz10,
    Hz20,
    Hz40,
    Hz80,
  };

  Magnetometer(MagRate rate, MagScale scale);

  void configure() override;
  void calibrate() override;

  Vec3<float> &getData() override;
  Vec3<int16_t> &getRawData() override;
};