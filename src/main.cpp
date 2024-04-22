
#include <Wire.h>
#include "sensors/magnetometer.hpp"

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!Serial)
    ;
}

void loop()
{
  Magnetometer mag;

  mag.compass();
}
