
#include "math.h"
#include "telemtry/accelerometer.hpp"
#include "telemtry/gyroscope.hpp"
#include "telemtry/magnetometer.hpp"
#include <Wire.h>
#include "ahrs.hpp"
#include "timer.hpp"
#include "utils/constants.hpp"
#include "recovery.hpp"
#include "buzzer.hpp"
#include "telemtry/innerBarometer.hpp"
#include <SerialFlash.h>
#include "flash.hpp"

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

void setup()
{
  Serial.begin(115200);

  while (!Serial)

    Wire.begin();
  Flash flash;
  Buzzer buzzer;
  Accelerometer accel(Accelerometer::Hz416, Accelerometer::g2);
  Gyroscope gyro(Gyroscope::Hz416, Gyroscope::dps2000);
  Magnetometer mag(Magnetometer::Hz80, Magnetometer::gauss4);
  // InnerBarometer innerBaro;
  Recovery recovery;

  Ahrs ahrs;

  Timer blockTimer;
  Timer launchTimer;

  States state = States::flying;

  // flash.printHumanReadable();
  // Serial.println(flash.address / sizeof(DiskData));
  // Serial.println(flash.address - SPI_FLASH_MEMORY_SIZE);

  DiskData data;
  SerialFlash.read(flash.address - sizeof(DiskData), &data, sizeof(DiskData));
  Serial.print(data.timestamp);
  // 16 777 216
  //  451 872

  while (true)
    ;

  while (true)
  {
    switch (state)
    {
    case States::calibrating:
    {
      gyro.calibrate();
      state = States::readyToTakeOff;
    }
    case States::readyToTakeOff:
    {
      buzzer.buzz();

      if (accel.getData().lenght() > TOOK_OFF_THRESHOLD)
      {
        state = States::flying;
        launchTimer.start();
        blockTimer.start();
        buzzer.stop();
      }
      break;
    }

    case States::flying:
    {

      if (blockTimer.doesTimeElapsed(BLOCK_PARACHUTE_TIME))
      {
        if (launchTimer.doesTimeElapsed(TIME_TO_OPEN_PARACHUTE))
        {
          state = States::landing;
          recovery.deploy(Recovery::TriggeredBy::Timer);
        }

        // if (innerBaro.altitude < ALTITUDE_TO_OPEN_PARACHUTE)
        // {
        // recovery.deploy(Recovery::TriggeredBy::Altitude);
        // }
        if (ahrs.rotations.x > ROTATION_X_THRESHOLD or ahrs.rotations.x < -ROTATION_X_THRESHOLD or ahrs.rotations.y > ROTATION_Y_THRESHOLD)
        {
          state = States::landing;
          recovery.deploy(Recovery::TriggeredBy::Rotation);
        }
      }

      break;
    }
    case States::landing:
    {
      if (accel.getData().lenght() < LANDING_THRESHOLD)
      {
        state = States::landed;
      }
      break;
    }
    case States::landed:
    {
      buzzer.playNyanCat();
    }
    default:
    {
      break;
    }
    }
    ahrs.update(accel.getData(), gyro.getData(), mag.getData());

    DiskData data;

    data.acc = accel.data;
    data.gyro = gyro.data;
    data.mag = mag.data;
    data.altitude = 0;
    data.pressure_1 = 0;
    data.pressure_2 = 0;
    data.timestamp = millis();

    flash.write(&data);

    // innerBaro.getData();
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
    Serial.print(ahrs.rotations.y);
    Serial.println();

    // Serial.println();
  }
}

void loop()
{
}
