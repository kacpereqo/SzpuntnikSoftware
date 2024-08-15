#pragma once

#include "sensor.hpp"
#include <LSM6.h>
#include <cstdint>

class Accelerometer : public Sensor
{
private:
  Vec3<int16_t> offset_raw;
  Vec3<int16_t> raw;
  Vec3<float> data;
  LSM6 &sensor;

public:
  enum AccelScale : uint8_t
  {
    g2,
    g4,
    g8,
    g16,
  };

  enum AccelRate : uint8_t
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

  Accelerometer(AccelRate rate, AccelScale scale);

  void configure() override;
  void calibrate() override;

  Vec3<float> &getData() override;
  Vec3<int16_t> &getRawData() override;
};