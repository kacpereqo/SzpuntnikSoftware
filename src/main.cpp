
#include "disk.hpp"
#include "math.h"
#include "telemtry/accelerometer.hpp"
#include "telemtry/gyroscope.hpp"
#include "telemtry/magnetometer.hpp"
#include <LSM6.h>
#include <Wire.h>
#include <ahrs.h>
#include "timer.hpp"
#include "utils/constants.hpp"
#include "recovery.hpp"
// #include "telemtry/innerBarometer.hpp"

void setup()
{
  Serial.begin(115200);
  while (!Serial)

    Wire.begin();
}

enum class States
{
  idle,
  calibrating,
  readyToTakeOff,
  flying,
  landing,
  landed,
};

void loop()
{

  // static Disk disk;
  Serial.println("HIGH")
      digitalWrite(D10, HIGH);
  Serial.println("LOW")
      digitalWrite(D10, Low);
  // static Accelerometer accel(Accelerometer::Hz416, Accelerometer::g2);
  // static Gyroscope gyro(Gyroscope::Hz416, Gyroscope::dps2000);
  // static Magnetometer mag(Magnetometer::Hz80, Magnetometer::gauss4);
  // // static InnerBarometer innerBaro;

  // static Disk disk;
  // static Ahrs ahrs;

  // static Timer blockTimer;
  // static Timer launchTimer;

  // static Recovery recovery;
  // static States state = States::calibrating;

  // switch (state)
  // {
  // case States::calibrating:
  // {
  //   gyro.calibrate();
  // case States::readyToTakeOff:
  //   bool tookOff = false;

  //   if (accel.tookOff())
  //   {
  //     state = States::flying;
  //   }
  //   launchTimer.start();
  // }

  // case States::flying:
  // {

  //   blockTimer.start();

  //   if (blockTimer.doesTimeElapsed(BLOCK_PARACHUTE_TIME))
  //   {
  //     if (launchTimer.doesTimeElapsed(TIME_TO_OPEN_PARACHUTE))
  //     {
  //       recovery.deploy(Recovery::TriggeredBy::Timer);
  //     }

  //     // if (innerBaro.getDataInMeters() < ALTITUDE_TO_OPEN_PARACHUTE)
  //     // {
  //     // recovery.deploy(Recovery::TriggeredBy::Altitude);
  //     // }

  //     if (ahrs.rotations.x > ROTATION_X_THRESHOLD)
  //     {
  //       recovery.deploy(Recovery::TriggeredBy::Rotation);
  //     }
  //   }

  //   break;
  // }
  // case States::landing:
  // {
  //   break;
  // }
  // case States::landed:
  // {
  //   break;
  // }
  // default:
  // {
  //   break;
  // }
  // }

  // disk.Save(accel.getData(), gyro.getData(), mag.getData(), ahrs.rotations);
  // ahrs.update(accel.getData(), gyro.getData(), mag.getData());

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

  // Serial.print("Rotations: ");
  // Serial.print((ahrs.rotations.x * 180) / M_PI);
  // Serial.print(" ");
  // Serial.print(ahrs.rotations.y * 180.0 / M_PI);
  // Serial.print(" ");
  // Serial.print(ahrs.rotations.z * 180.0 / M_PI);

  // Serial.println();
  // delay(1000.0 / 100.0);
}
