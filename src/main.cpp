
#include <Wire.h>
#include "LSM6DS33.hpp"
#include "LPS25H.hpp"
#include "magnetometer.hpp"
#include "rotation.hpp"

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!Serial)
    ;
}

void loop()
{
  // Magnetometer magnetometer;
  // magnetometer.compass();
  static Rotation rotation;

  rotation.updateRotation();
}
