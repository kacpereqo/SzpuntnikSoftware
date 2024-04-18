
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
  static int count = 0;
  for (;;)
  {
    Serial.println(count++);
    delay(10);
  }
}
