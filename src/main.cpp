
#include <Wire.h>
#include "LSM6DS33.hpp"

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!Serial)
    ;
}

void loop()
{
  static LSM6DS33 imu;

  imu.configureAccel(LSM6DS33::AccelScale::g16, LSM6DS33::AccelRate::Hz1660);

  auto accel = imu.readGyro();
  Serial.print("gyro: ");
  Serial.print(accel[0]);
  Serial.print(", ");
  Serial.print(accel[1]);
  Serial.print(", ");
  Serial.println(accel[2]);
  delay(100);
}