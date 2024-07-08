#include "accelerometer.hpp"
#include "utils/constants.hpp"
#include "utils/singletons.hpp"
#include <cstdint>

Accelerometer::Accelerometer(AccelRate rate, AccelScale scale)
    : sensor(getLSM6()) {
  this->sensor = getLSM6();
  this->rate = rate;
  this->scale = scale;
}

void Accelerometer::configure() {}

void Accelerometer::calibrate() {
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    offset_raw += this->getRawData();
  }

  offset_raw /= CALIBRATION_SAMPLES;
}

Vec3<float> &Accelerometer::getData() {
  Vec3<int16_t> raw = this->getRawData();

  Vec3<float> data = {
      raw.x - offset_raw.x / this->scale_factor,
      raw.y - offset_raw.y / this->scale_factor,
      raw.z - offset_raw.z / this->scale_factor,
  };

  return data;
}

Vec3<int16_t> &Accelerometer::getRawData() {
  this->sensor.readAcc();

  Vec3<int16_t> raw = {this->sensor.a.x, this->sensor.a.y, this->sensor.a.z};

  return raw;
}
