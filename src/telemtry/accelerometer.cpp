#include "accelerometer.hpp"
#include "Arduino.h"
#include "utils/constants.hpp"
#include "utils/singletons.hpp"
#include <cstdint>

Accelerometer::Accelerometer(AccelRate rate, AccelScale scale)
    : sensor(getLSM6())
{
  this->sensor = getLSM6();
  this->rate = rate;
  this->scale = scale;
  this->scale_factor = 1 << (16 - (scale + 2));
  this->sensor.enableDefault();

  // calibrate();
}

void Accelerometer::configure() {}

void Accelerometer::calibrate()
{
  for (int i = 0; i < CALIBRATION_SAMPLES; i++)
  {
    offset_raw += this->getRawData();

    delay(CALIBRATION_DELAY);
  }

  offset_raw /= CALIBRATION_SAMPLES;

  Serial.print("Calibrated Accelerometer Offset");
  Serial.print(" X: ");
  Serial.print(offset_raw.x);
  Serial.print(" Y: ");
  Serial.print(offset_raw.y);
  Serial.print(" Z: ");
  Serial.println(offset_raw.z);
}

Vec3<float> &Accelerometer::getData()
{
  (void)this->getRawData();

  this->data = {
      (this->raw.x - offset_raw.x) / this->scale_factor,
      (this->raw.y - offset_raw.y) / this->scale_factor,
      (this->raw.z - offset_raw.z) / this->scale_factor,
  };

  return data;
}

Vec3<int16_t> &Accelerometer::getRawData()
{
  this->sensor.readAcc();

  this->raw = {this->sensor.a.x, this->sensor.a.y, this->sensor.a.z};

  return raw;
}

bool Accelerometer::tookOff()
{
  this->data.lenght() > TOOK_OFF_THRESHOLD;
}