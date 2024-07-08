
#include "disk.hpp"
#include "telemtry\accelerometer.hpp"
#include "telemtry\gyroscope.hpp"
#include "telemtry\magnetometer.hpp"
#include <LSM6.h>
#include <Wire.h>
#include <ahrs.h>

void setup() {}

enum class States {
  idle,
  calibrating,
  readyToTakeOff,
  flying,
  landing,
  landed,
};

void loop() {
  static Accelerometer accel(Accelerometer::Hz416, Accelerometer::g2);
  static Gyroscope gyro(Gyroscope::Hz416, Gyroscope::dps2000);
  static Magnetometer mag(Magnetometer::Hz80, Magnetometer::gauss4);

  static Disk disk;
  static Ahrs ahrs;

  static States state = States::idle;

  switch (state) {
  case States::idle:
    break;
  case States::calibrating:
    break;
  case States::readyToTakeOff:
    break;
  case States::flying:
    break;
  case States::landing:
    break;
  case States::landed:
    break;
  default:
    break;
  }

  if (state >= States::flying) {
    disk.Save(accel.getData(), gyro.getData(), mag.getData(), ahrs.rotations);
  }

  ahrs.update(accel.getData(), gyro.getData(), mag.getData());
}