
// #include <Wire.h>
// #include "imu.hpp"
// #include "disk.hpp"
// #include "rc.hpp"
// #include "recovery.hpp"

// void setup()
// {
//   Serial.begin(115200);
//   Wire.begin();
//   while (!Serial)
//     ;
// }

// enum class State
// {
//   calibration,
//   waitingForTakeoff,
//   flight,
//   falling,
//   landed,
// };

// String toString(State state)
// {
//   switch (state)
//   {
//   case State::calibration:
//     return "calibration";
//   case State::waitingForTakeoff:
//     return "waitingForTakeoff";
//   case State::flight:
//     return "flight";
//   case State::falling:
//     return "falling";
//   case State::landed:
//     return "landed";
//   }
// }
// void loop()
// {
//   static Imu imu;
//   static Disk disk;
//   static RadioCommunication rc;
//   static Recovery recovery;

//   static State state = State::flight;

//   constexpr int interval = 100; // in milliseconds

//   constexpr int parachuteDeploymentTime = 6000; // in milliseconds

//   constexpr float altitudeThreshold = -0.5;    // in meters
//   constexpr float accelerationThreshold = 0.5; // in g force
//   constexpr float angleThreshhold = 50;        // in degrees

//   static int launchTime = 0;

//   static bool pitch = false;
//   static bool roll = false;
//   static bool yaw = false;

//   static long lastUpdate = millis();

//   switch (state)
//   {
//   case State::calibration:
//   {
//     imu.calibrate();
//     state = State::waitingForTakeoff;
//     delay(interval);
//   }
//   case State::waitingForTakeoff:
//   {

//     // 1 - 1g
//     float resultantAcceleration = sqrt(pow(imu.accel.x, 2) + pow(imu.accel.y, 2) + pow(imu.accel.z, 2));

//     if (resultantAcceleration != 0)
//     {

//       if (abs(resultantAcceleration - 1) > accelerationThreshold)
//       {
//         state = State::flight;
//       }
//     }

//     break;
//   }
//   case State::flight:
//   {

//     // ways to open the parachute

//     if (imu.pitch > angleThreshhold || imu.pitch < -angleThreshhold)
//     {
//       recovery.deploy();
//       pitch = true;
//       // Serial.println("Pitch");
//       // state = State::falling;
//     }

//     if (imu.roll > angleThreshhold || imu.roll < -angleThreshhold)
//     {
//       recovery.deploy();
//       roll = true;
//       // Serial.println("Roll");
//       // state = State::falling;
//     }

//     if (imu.yaw < -angleThreshhold)
//     {
//       recovery.deploy();
//       yaw = true;
//       // Serial.println("Yaw");
//       // state = State::falling;
//     }
//   }
//   case State::falling:
//   {

//     break;
//   }
//   case State::landed:
//   {
//     // disk.save();
//     break;
//   }
//   }

//   if (state != State::landed || state != State::calibration)
//   {
//     imu.update();
//     Serial.print(pitch);
//     Serial.print(",");
//     Serial.print(roll);
//     Serial.print(",");
//     Serial.print(yaw);
//     Serial.println();

//     roll = false;
//     pitch = false;
//     yaw = false;
//     // Serial.println(toString(state));
//     // Serial.print(",");
//     // imu.readings();
//     // disk.save({
//     //     millis(),
//     //     imu.imu.readRawAccel(),
//     //     imu.imu.readRawGyro(),
//     //     imu.magnetometer.readMag(),
//     // });

//     // disk.saveToFlash(imu.readings());
//   }
//   // delay(1000 / 20);
// }

#include <RadioLib.h>

// nRF24 has the following connections:
// CS pin:    10
// IRQ pin:   2
// CE pin:    3
nRF24 radio = new Module(10, 2, 3);

void setFlag();

bool switch1 = false;
bool switch2 = false;
bool switch3 = false;
bool switch4 = false;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.print(F("[nRF24] Initializing ... "));
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.println(F("success!"));
  }
  else
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true)
      ;
  }

  Serial.print(F("[nRF24] Setting address for receive pipe 0 ... "));
  byte addr[] = {0x01, 0x23, 0x45, 0x67, 0x89};
  state = radio.setReceivePipe(0, addr);
  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.println(F("success!"));
  }
  else
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true)
      ;
  }

  radio.setPacketReceivedAction(setFlag);

  // start listening
  Serial.print(F("[nRF24] Starting to listen ... "));
  state = radio.startReceive();
  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.println(F("success!"));
  }
  else
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true)
      ;
  }
}

volatile bool receivedFlag = false;

void setFlag(void)
{

  receivedFlag = true;
}

void loop()
{

  if (receivedFlag)
  {

    receivedFlag = false;

    String str;
    int state = radio.readData(str);

    if (state == RADIOLIB_ERR_NONE)
    {
      Serial.println(F("[nRF24] Received packet!"));

      Serial.print(F("[nRF24] Data:\t\t"));
      Serial.println(str);
    }
    else
    {
      Serial.print(F("[nRF24] Failed, code "));
      Serial.println(state);
    }

    radio.startReceive();
  }
}