
#include "disk.hpp"
#include "math.h"
#include "telemtry/accelerometer.hpp"
#include "telemtry/gyroscope.hpp"
#include "telemtry/magnetometer.hpp"
#include <LSM6.h>
#include <Wire.h>
#include "ahrs.hpp"
#include "timer.hpp"
#include "utils/constants.hpp"
#include "recovery.hpp"
#include "buzzer.hpp"
#include "telemtry/innerBarometer.hpp"

void setup()
{
  Serial.begin(115200);

  while (!Serial)

    Wire.begin();
}

enum class States
{
  idle = 0,
  calibrating = 1,
  readyToTakeOff = 2,
  flying = 3,
  landing = 4,
  landed = 5,
  test = 6,
};

void loop()
{

  static Disk disk;

  static Vec3<float> acc{random(0, 10), random(0, 10), random(0, 10)};
  static Vec3<float> gyro{1, 2, 3};
  static Vec3<float> mag{1, 2, 3};
  static Vec3<float> rotation{1, 2, 3};

  DiskData data{
      acc,
      gyro,
      mag,
      rotation,
      1,
      2,

      millis()};
  // disk.save(data);
  disk.read();
  // static Buzzer buzzer;
  // static Accelerometer accel(Accelerometer::Hz416, Accelerometer::g2);
  // static Gyroscope gyro(Gyroscope::Hz416, Gyroscope::dps2000);
  // static Magnetometer mag(Magnetometer::Hz80, Magnetometer::gauss4);
  // static InnerBarometer innerBaro;
  // static Recovery recovery;

  // static Ahrs ahrs;

  // static Timer blockTimer;
  // static Timer launchTimer;

  // static States state = States::flying;

  // recovery.test();

  // switch (state)
  // {
  // case States::calibrating:
  // {
  //   gyro.calibrate();
  //   state = States::readyToTakeOff;
  // }
  // case States::readyToTakeOff:
  // {
  //   buzzer.buzz();

  //   if (accel.getData().lenght() > TOOK_OFF_THRESHOLD)
  //   {
  //     state = States::flying;
  //     launchTimer.start();
  //     blockTimer.start();
  //     buzzer.stop();
  //   }
  //   break;
  // }

  // case States::flying:
  // {

  //   if (blockTimer.doesTimeElapsed(BLOCK_PARACHUTE_TIME))
  //   {
  //     if (launchTimer.doesTimeElapsed(TIME_TO_OPEN_PARACHUTE))
  //     {
  //       state = States::landing;
  //       recovery.deploy(Recovery::TriggeredBy::Timer);
  //     }

  //     if (innerBaro.altitude < ALTITUDE_TO_OPEN_PARACHUTE)
  //     {
  //       recovery.deploy(Recovery::TriggeredBy::Altitude);
  //     }
  //     if (ahrs.rotations.x > ROTATION_X_THRESHOLD or ahrs.rotations.x < -ROTATION_X_THRESHOLD or ahrs.rotations.y > ROTATION_Y_THRESHOLD)
  //     {
  //       state = States::landing;
  //       recovery.deploy(Recovery::TriggeredBy::Rotation);
  //     }
  //   }

  //   break;
  // }
  // case States::landing:
  // {
  //   if (accel.getData().lenght() < LANDING_THRESHOLD)
  //   {
  //     state = States::landed;
  //   }
  //   break;
  // }
  // case States::landed:
  // {
  //   buzzer.playNyanCat();
  // }
  // default:
  // {
  //   break;
  // }
  // }

  // ahrs.update(accel.getData(), gyro.getData(), mag.getData());
  // innerBaro.getData();
  // // // print everything
  // // Serial.print("Accel: ");
  // // Serial.print(accel.getData().x);
  // // Serial.print(" ");
  // // Serial.print(accel.getData().y);
  // // Serial.print(" ");
  // // Serial.print(accel.getData().z);

  // // Serial.print("|");

  // // Serial.print("Gyro: ");
  // // Serial.print(gyro.getData().x);
  // // Serial.print(" ");
  // // Serial.print(gyro.getData().y);
  // // Serial.print(" ");
  // // Serial.print(gyro.getData().z);

  // // Serial.print("|");

  // // Serial.print("Mag: ");
  // // Serial.print(mag.getData().x);
  // // Serial.print(" ");
  // // Serial.print(mag.getData().y);
  // // Serial.print(" ");
  // // Serial.print(mag.getData().z);

  // // Serial.print("|");

  // // Serial.print("Rotations: ");
  // // Serial.print(",");
  // // Serial.print(ahrs.rotations.y * 180.0 / M_PI);
  // // Serial.print(",");
  // // Serial.print(180);
  // // Serial.print(",");
  // // Serial.print(-180);

  // // Serial.println();
}
