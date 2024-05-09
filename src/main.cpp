
#include <Wire.h>
#include "imu.hpp"
#include "disk.hpp"
#include "rc.hpp"
#include "recovery.hpp"

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  while (!Serial)
    ;
}

enum class State
{
  calibration,
  waitingForTakeoff,
  flight,
  falling,
  landed,
};

void loop()
{
  static Imu imu;
  static Disk disk;
  static RadioCommunication rc;
  static Recovery recovery;

  static State state = State::calibration;

  constexpr int interval = 200; // in milliseconds

  constexpr float altitudeThreshold = -0.5;    // in meters
  constexpr float accelerationThreshold = 0.1; // in g force
  constexpr float angleThreshhold = 45;        // in degrees

  static long lastUpdate = millis();

  switch (state)
  {
  case State::calibration:
  {
    imu.calibrate();
    state = State::waitingForTakeoff;
  }
  case State::waitingForTakeoff:
  {

    static float lastAcceleration = imu.accel.x;

    if (millis() - lastUpdate > interval)
    {
      if (lastAcceleration - imu.accel.x < accelerationThreshold)
      {
        state = State::flight;
      }
      lastAcceleration = imu.accel.x;
    }

    break;
  }
  case State::flight:
  {

    static float lastAltitude = imu.altitude;

    // ways to open the parachute

    if (millis() - lastUpdate > interval)
    {
      if (imu.altitude - lastAltitude < altitudeThreshold)
      {
        recovery.deploy();
        state = State::falling;
      }
      lastAltitude = imu.altitude;
    }

    if (imu.pitch > angleThreshhold || imu.pitch < -angleThreshhold)
    {
      recovery.deploy();
      state = State::falling;
    }

    if (imu.roll > angleThreshhold || imu.roll < -angleThreshhold)
    {
      recovery.deploy();
      state = State::falling;
    }

    lastUpdate = millis();

    break;
  }
  case State::falling:
  {

    break;
  }
  case State::landed:
  {
    // disk.save();
    break;
  }
  }

  if (state != State::landed || state != State::calibration)
  {
    imu.update();
    imu.readings();
    disk.save({
        millis(),
        imu.imu.readRawAccel(),
        imu.imu.readRawGyro(),
        imu.magnetometer.readMag(),
    });

    // disk.saveToFlash(imu.readings());
  }
}
