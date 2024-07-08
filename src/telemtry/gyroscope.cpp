#include "gyroscope.hpp"
#include "utils/singletons.hpp"

Gyroscope::Gyroscope(GyroRate rate, GyroScale scale) : sensor(getLSM6()) {
  this->sensor = getLSM6();
}

void Gyroscope::configure() {}