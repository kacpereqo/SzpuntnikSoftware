
#include <Wire.h>
#include "LSM6DS33.hpp"
#include "LPS25H.hpp"

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!Serial)
    ;
}

void loop()
{
  // static LSM6DS33 imu;
  static LPS25H ps;

  auto data = ps.readAltitude();
  Serial.print("alltitude: ");
  Serial.print(data);
  Serial.println();
}
