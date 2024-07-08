#include "magnetometer.hpp"
#include "utils/singletons.hpp"

Magnetometer::Magnetometer(MagRate rate, MagScale scale)
    : sensor(getLIS3MDL()) {
  this->sensor = getLIS3MDL();
}

void Magnetometer::configure() {}

void Magnetometer::calibrate() {}

Vec3<float> &Magnetometer::getData() {}

Vec3<int16_t> &Magnetometer::getRawData() {}
