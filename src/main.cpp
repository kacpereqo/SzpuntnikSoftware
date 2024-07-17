
#include "disk.hpp"
#include "math.h"
#include "telemtry\accelerometer.hpp"
#include "telemtry\gyroscope.hpp"
#include "telemtry\magnetometer.hpp"
#include <LSM6.h>
#include <Wire.h>
#include <ahrs.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)

    Wire.begin();
}

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

  // disk.Save(accel.getData(), gyro.getData(), mag.getData(), ahrs.rotations);
  ahrs.update(accel.getData(), gyro.getData(), mag.getData());

  // // print everything
  // Serial.print("Accel: ");
  // Serial.print(accel.getData().x);
  // Serial.print(" ");
  // Serial.print(accel.getData().y);
  // Serial.print(" ");
  // Serial.print(accel.getData().z);

  // Serial.print("|");

  // Serial.print("Gyro: ");
  // Serial.print(gyro.getData().x);
  // Serial.print(" ");
  // Serial.print(gyro.getData().y);
  // Serial.print(" ");
  // Serial.print(gyro.getData().z);

  // Serial.print("|");

  // Serial.print("Mag: ");
  // Serial.print(mag.getData().x);
  // Serial.print(" ");
  // Serial.print(mag.getData().y);
  // Serial.print(" ");
  // Serial.print(mag.getData().z);

  // Serial.print("|");

  Serial.print("Rotations: ");
  Serial.print((ahrs.rotations.x * 180) / M_PI);
  Serial.print(" ");
  Serial.print(ahrs.rotations.y * 180.0 / M_PI);
  Serial.print(" ");
  Serial.print(ahrs.rotations.z * 180.0 / M_PI);

  Serial.println();
  // delay(1000.0 / 100.0);
}
