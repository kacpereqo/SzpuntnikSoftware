
#include <Wire.h>
#include "LSM6DS33.hpp"
#include "LPS25H.hpp"
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
  static Rotation sex;
  sex.updateRotation();
}
