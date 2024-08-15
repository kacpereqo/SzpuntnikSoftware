#pragma once

#include "sensor.hpp"
#include <LSM6.h>
#include <cstdint>

class Gyroscope : public Sensor
{
private:
  Vec3<int16_t> raw;
  Vec3<float> data;
  LSM6 &sensor;

public:
  enum GyroScale : uint8_t
  {
    dps125,
    dps245,
    dps500,
    dps1000,
    dps2000,
  };

  enum GyroRate : uint8_t
  {
    Hz13,
    Hz26,
    Hz52,
    Hz104,
    Hz208,
    Hz416,
    Hz833,
    Hz1660,
  };

  Gyroscope(GyroRate rate, GyroScale scale);

  void configure() override;
  void calibrate() override;

  Vec3<float> &getData() override;
  Vec3<int16_t> &getRawData() override;
};