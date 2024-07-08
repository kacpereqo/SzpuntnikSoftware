#include "accelerometer.hpp"
#include "utils/singletons.hpp"

Accelerometer::Accelerometer(AccelRate rate, AccelScale scale)
    : sensor(getLSM6()) {
  this->sensor = getLSM6();
}

void Accelerometer::configure() {}

void Accelerometer::calibrate() {}

Vec3<float> &Accelerometer::getData() {}

Vec3<int16_t> &Accelerometer::getRawData() {}
