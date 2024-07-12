#include "magnetometer.hpp"
#include "utils/singletons.hpp"

Magnetometer::Magnetometer(MagRate rate, MagScale scale)
    : sensor(getLIS3MDL()) {
  this->sensor = getLIS3MDL();

  this->scale_factor = scale;

  this->min_values_raw = {INT16_MAX, INT16_MAX, INT16_MAX};
  this->max_values_raw = {INT16_MIN, INT16_MIN, INT16_MIN};

  this->sensor.enableDefault();
}

void Magnetometer::configure() {}

void Magnetometer::calibrate() {
  if (this->min_values_raw.x > this->sensor.m.x) {
    this->min_values_raw.x = this->sensor.m.x;
  }

  if (this->min_values_raw.y > this->sensor.m.y) {
    this->min_values_raw.y = this->sensor.m.y;
  }

  if (this->min_values_raw.z > this->sensor.m.z) {
    this->min_values_raw.z = this->sensor.m.z;
  }

  if (this->max_values_raw.x < this->sensor.m.x) {
    this->max_values_raw.x = this->sensor.m.x;
  }

  if (this->max_values_raw.y < this->sensor.m.y) {
    this->max_values_raw.y = this->sensor.m.y;
  }

  if (this->max_values_raw.z < this->sensor.m.z) {
    this->max_values_raw.z = this->sensor.m.z;
  }
}

Vec3<float> &Magnetometer::getData() {
  this->calibrate();
  Vec3<int16_t> raw = this->getRawData();

  this->data = {
      // normalize
      (raw.x - this->min_values_raw.x) /
              (float)(this->max_values_raw.x - this->min_values_raw.x) * 2.0f -
          1.0f,
      (raw.y - this->min_values_raw.y) /
              (float)(this->max_values_raw.y - this->min_values_raw.y) * 2.0f -
          1.0f,
      (raw.z - this->min_values_raw.z) /
              (float)(this->max_values_raw.z - this->min_values_raw.z) * 2.0f -
          1.0f,
  };

  return data;
}

Vec3<int16_t> &Magnetometer::getRawData() {
  this->sensor.read();

  this->raw = {this->sensor.m.x, this->sensor.m.y, this->sensor.m.z};

  return raw;
}
