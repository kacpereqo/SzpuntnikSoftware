#include "gyroscope.hpp"
#include "utils/singletons.hpp"

Gyroscope::Gyroscope(GyroRate rate, GyroScale scale) : sensor(getLSM6()) {
  this->sensor = getLSM6();
  this->sensor.enableDefault();
}

void Gyroscope::configure() {}

void Gyroscope::calibrate() {}

Vec3<float> &Gyroscope::getData() {
  Vec3<int16_t> raw = this->getRawData();

  Vec3<float> data = {
      raw.x / this->scale_factor,
      raw.y / this->scale_factor,
      raw.z / this->scale_factor,
  };

  return data;
}

Vec3<int16_t> &Gyroscope::getRawData() {
  this->sensor.readGyro();

  this->raw = {this->sensor.g.x, this->sensor.g.y, this->sensor.g.z};

  return raw;
}