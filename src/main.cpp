
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

  pinMode(D2, INPUT_PULLUP);
  Recovery recovery;

  Flash flash;
  Serial.begin(115200);
  while (!Serial)
    ;
  ;

  // flash.eraseAll();
  // while (!SerialFlash.ready())
  // ;

  // Serial.println("done");

  // flash.printHumanReadable();
  // while (true)
  bool safetyPin = false;
  bool safetyPinLoop = false;

sex:
  do
  {
    safetyPin = digitalRead(D2);
  } while (safetyPin == 0);
  recovery.servo.write(140);

  {
    Wire.begin();
    Buzzer buzzer;
    Accelerometer accel(Accelerometer::Hz416, Accelerometer::g2);
    Gyroscope gyro(Gyroscope::Hz416, Gyroscope::dps245);
    Magnetometer mag(Magnetometer::Hz80, Magnetometer::gauss4);
    Barometer innerBaro(0x77);
    // Barometer outerBaro;

    Ahrs ahrs;

    Timer blockTimer;
    Timer launchTimer;

    States state = States::calibrating;

    DiskData data;

    while (true)
    {
      Serial.println((int)state);

      do
      {

        safetyPin = digitalRead(D2);
        if (safetyPin == LOW)
        {
          safetyPinLoop = true;
        }
      } while (safetyPinLoop == false);

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

        if (accel.data.lenght() > TOOK_OFF_THRESHOLD)
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
        }

        break;
      }
      case States::landing:
      {
        for (;;)
        {
          if (digitalRead(D2) == LOW)
          {

            goto sex;
          }
          // buzzer.playNyanCat();
          // buzzer.buzz();
          break;
        }
      default:
      {
        break;
      }
      }

        // not using due to the fact mateusz is MAD!!!
        // ahrs.update(accel.data, gyro.data, mag.data);

        //   DiskData data;

        //   data.acc = accel.data;
        //   data.gyro = gyro.data;
        //   data.mag.x = mag.raw.x;
        //   data.mag.y = mag.raw.y;
        //   data.mag.z = mag.raw.z;
        //   data.pressure_inner = innerBaro.pressure;
        //   data.pressure_outer = outerBaro.pressure;
        //   data.humidity_inner = innerBaro.humidity;
        //   data.humidity_outer = outerBaro.humidity;
        //   data.temperature_inner = innerBaro.temperature;
        //   data.temperature_outer = outerBaro.temperature;
        //   data.timestamp = millis();

        //   flash.write(&data);

        //   innerBaro.getData();
        //   outerBaro.getData();

        accel.getData();
        gyro.getData();
        mag.getData();
        //

        // delay(100);
      }
    }
  }
  void loop()
  {
  }
