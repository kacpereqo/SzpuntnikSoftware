
#include <Wire.h>
#include "imu.hpp"
#include "disk.hpp"
#include "recovery.hpp"
#include "speaker.hpp"
#include <RadioLib.h>

bool receivedFlag = false;

nRF24 radio = new Module(10, 2, 3);

void setFlag()
{
  receivedFlag = true;
}

// blink led

void blink()
{
  //   digitalWrite(13, HIGH);
  //   delay(10);
  //   digitalWrite(13, LOW);
  //   delay(10);
}

void setup()
{

  // Serial.begin(115200);
  Wire.begin();

  while (!Serial)
    ;

  // Serial.print(F("[nRF24] Initializing ... "));
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE)
  {
    // Serial.println(F("success!"));
  }
  else
  {
    // Serial.print(F("failed, code "));
    // Serial.println(state);
    while (true)
      ;
  }

  // Serial.print(F("[nRF24] Setting address for receive pipe 0 ... "));
  byte addr[] = {0x01, 0x23, 0x45, 0x67, 0x89};
  state = radio.setReceivePipe(0, addr);
  if (state == RADIOLIB_ERR_NONE)
  {
    // Serial.println(F("success!"));
  }
  else
  {
    // Serial.print(F("failed, code "));
    // Serial.println(state);
    while (true)
      ;
  }
}

enum class State
{
  calibration,
  waitingForTakeoff,
  flight,
  falling,
  landed,
};

String toString(State state)
{
  switch (state)
  {
  case State::calibration:
    return "calibration";
  case State::waitingForTakeoff:
    return "waitingForTakeoff";
  case State::flight:
    return "flight";
  case State::falling:
    return "falling";
  case State::landed:
    return "landed";
  }
}
void loop()
{

  static Speaker speaker;
  blink();
  blink();
  static Imu imu;
  blink();
  blink();

  static Disk disk;
  static Recovery recovery;
  static State state = State::calibration;

  constexpr int interval = 100; // in milliseconds

  constexpr int parachuteDeploymentTime = 6000; // in milliseconds
  constexpr int blockTime = 1000;               // in milliseconds

  // constexpr float altitudeThreshold = -0.5;    // in meters
  constexpr float accelerationThreshold = 0.5; // in g force
  constexpr float angleThreshhold = 50;        // in degrees

  static int launchTime = 0;

  static bool pitch = false;
  static bool roll = false;
  static bool yaw = false;

  static bool switch1 = false;
  static bool switch2 = false;
  static bool switch3 = false;
  static bool switch4 = false;

  static long lastUpdate = millis();

  if (switch1 == true)
  {
    recovery.deploy();
  }
  else
  {
    recovery.open();
  }

  if (switch2 == true)
  {
    state = State::calibration;
  }

  switch (state)
  {
  case State::calibration:
  {
    imu.calibrate();
    state = State::waitingForTakeoff;
    // Serial.println("Calibrated");
  }
  case State::waitingForTakeoff:
  {
    if (switch1 == true)
    {
      break;
    }
    speaker.play();
    // 1 - 1g
    float resultantAcceleration = sqrt(pow(imu.accel.x, 2) + pow(imu.accel.y, 2) + pow(imu.accel.z, 2));

    if (resultantAcceleration != 0)
    {

      if (abs(resultantAcceleration - 1) > accelerationThreshold)
      {
        launchTime = millis();
        state = State::flight;
      }
    }

    break;
  }
  case State::flight:
  {
    speaker.play();
    if (millis() - launchTime > blockTime)
    {
      if (imu.pitch > angleThreshhold || imu.pitch < -angleThreshhold)
      {
        recovery.deploy();
      }

      if (imu.roll > angleThreshhold || imu.roll < -angleThreshhold)
      {
        recovery.deploy();
      }

      if (imu.yaw < -angleThreshhold)
      {
        recovery.deploy();
      }
      if (millis() - launchTime > parachuteDeploymentTime)
      {
        recovery.deploy();
      }
    }
  }
  }

  imu.update();

  imu.readings();

  disk.save({
      millis(),
      imu.imu.readRawAccel(),
      imu.imu.readRawGyro(),
      imu.magnetometer.readMag(),
      imu.barometer.readPressure(),
      imu.barometer.readTemperature(),
  });

  String str;
  int radioState = radio.receive(str);

  if (radioState == RADIOLIB_ERR_NONE)
  {
    switch1 = str[0] == '1';
    switch2 = str[1] == '1';
    switch3 = str[2] == '1';
    switch4 = str[3] == '1';
  }
}
