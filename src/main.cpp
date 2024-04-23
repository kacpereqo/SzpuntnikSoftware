
#include <Wire.h>
#include "imu.hpp"

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!Serial)
    ;
}

enum class State
{
  calibration,
  flight,
  falling,
  landed,
};

void loop()
{
  static Imu imu;

  imu.update();

  Serial.print("Pitch: ");
  Serial.print(imu.pitch);
  Serial.print(" Yaw: ");
  Serial.print(imu.yaw);
  Serial.print(" Roll: ");
  Serial.print(imu.roll);
  Serial.print(" Preassure: ");
  Serial.print(imu.preassure);
  Serial.print(" Alltitude: ");
  Serial.println(imu.altitude);
}
