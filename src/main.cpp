
// #include <Wire.h>
// #include "imu.hpp"
// #include "disk.hpp"
// #include "recovery.hpp"
// #include <RadioLib.h>

// bool receivedFlag = false;

// nRF24 radio = new Module(10, 2, 3);

// void setFlag()
// {
//   receivedFlag = true;
// }

// void setup()
// {

//   Serial.begin(115200);
//   Wire.begin();
//   while (!Serial)
//     ;

//   Serial.print(F("[nRF24] Initializing ... "));
//   int state = radio.begin();
//   if (state == RADIOLIB_ERR_NONE)
//   {
//     Serial.println(F("success!"));
//   }
//   else
//   {
//     Serial.print(F("failed, code "));
//     Serial.println(state);
//     while (true)
//       ;
//   }

//   // set receive pipe 0 address
//   // NOTE: address width in bytes MUST be equal to the
//   //       width set in begin() or setAddressWidth()
//   //       methods (5 by default)
//   Serial.print(F("[nRF24] Setting address for receive pipe 0 ... "));
//   byte addr[] = {0x01, 0x23, 0x45, 0x67, 0x89};
//   state = radio.setReceivePipe(0, addr);
//   if (state == RADIOLIB_ERR_NONE)
//   {
//     Serial.println(F("success!"));
//   }
//   else
//   {
//     Serial.print(F("failed, code "));
//     Serial.println(state);
//     while (true)
//       ;
//   }
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

//   static bool switch1 = false;
//   static bool switch2 = false;
//   static bool switch3 = false;
//   static bool switch4 = false;

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
//       // recovery.deploy();
//       pitch = true;
//       // Serial.println("Pitch");
//       // state = State::falling;
//     }

//     if (imu.roll > angleThreshhold || imu.roll < -angleThreshhold)
//     {
//       // recovery.deploy();
//       roll = true;
//       // Serial.println("Roll");
//       // state = State::falling;
//     }

//     if (imu.yaw < -angleThreshhold)
//     {
//       // recovery.deploy();
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
//     // Serial.print(pitch);
//     // Serial.print(",");
//     // Serial.print(roll);
//     // Serial.print(",");
//     // Serial.print(yaw);
//     // Serial.println();

//     // roll = false;
//     // pitch = false;
//     // yaw = false;
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

//   if (switch1)
//   {
//     recovery.deploy();
//   }

//   Serial.print(F("[nRF24] Waiting for incoming transmission ... "));

//   // you can receive data as an Arduino String
//   // NOTE: receive() is a blocking method!
//   //       See example ReceiveInterrupt for details
//   //       on non-blocking reception method.
//   String str;
//   int radioState = radio.receive(str);

//   // you can also receive data as byte array
//   /*
//     byte byteArr[8];
//     int state = radio.receive(byteArr, 8);
//   */

//   if (radioState == RADIOLIB_ERR_NONE)
//   {
//     // packet was successfully received
//     Serial.println(F("success!"));

//     // print the data of the packet
//     Serial.print(F("[nRF24] Data:\t\t"));
//     Serial.println(str);

//     switch1 = str[0] == '1';
//     switch2 = str[1] == '1';
//     switch3 = str[2] == '1';
//     switch4 = str[3] == '1';
//   }
//   else if (radioState == RADIOLIB_ERR_RX_TIMEOUT)
//   {
//     Serial.println(F("timeout!"));
//   }
//   else
//   {
//     Serial.print(F("failed, code "));
//     Serial.println(radioState);
//   }
// }

#include <Arduino.h>

#define NOTE_B0 31

#define NOTE_C1 33

#define NOTE_CS1 35

#define NOTE_D1 37

#define NOTE_DS1 39

#define NOTE_E1 41

#define NOTE_F1 44

#define NOTE_FS1 46

#define NOTE_G1 49

#define NOTE_GS1 52

#define NOTE_A1 55

#define NOTE_AS1 58

#define NOTE_B1 62

#define NOTE_C2 65

#define NOTE_CS2 69

#define NOTE_D2 73

#define NOTE_DS2 78

#define NOTE_E2 82

#define NOTE_F2 87

#define NOTE_FS2 93

#define NOTE_G2 98

#define NOTE_GS2 104

#define NOTE_A2 110

#define NOTE_AS2 117

#define NOTE_B2 123

#define NOTE_C3 131

#define NOTE_CS3 139

#define NOTE_D3 147

#define NOTE_DS3 156

#define NOTE_E3 165

#define NOTE_F3 175

#define NOTE_FS3 185

#define NOTE_G3 196

#define NOTE_GS3 208

#define NOTE_A3 220

#define NOTE_AS3 233

#define NOTE_B3 247

#define NOTE_C4 262

#define NOTE_CS4 277

#define NOTE_D4 294

#define NOTE_DS4 311

#define NOTE_E4 330

#define NOTE_F4 349

#define NOTE_FS4 370

#define NOTE_G4 392

#define NOTE_GS4 415

#define NOTE_A4 440

#define NOTE_AS4 466

#define NOTE_B4 494

#define NOTE_C5 523

#define NOTE_CS5 554

#define NOTE_D5 587

#define NOTE_DS5 622

#define NOTE_E5 659

#define NOTE_F5 698

#define NOTE_FS5 740

#define NOTE_G5 784

#define NOTE_GS5 831

#define NOTE_A5 880

#define NOTE_AS5 932

#define NOTE_B5 988

#define NOTE_C6 1047

#define NOTE_CS6 1109

#define NOTE_D6 1175

#define NOTE_DS6 1245

#define NOTE_E6 1319

#define NOTE_F6 1397

#define NOTE_FS6 1480

#define NOTE_G6 1568

#define NOTE_GS6 1661

#define NOTE_A6 1760

#define NOTE_AS6 1865

#define NOTE_B6 1976

#define NOTE_C7 2093

#define NOTE_CS7 2217

#define NOTE_D7 2349

#define NOTE_DS7 2489

#define NOTE_E7 2637

#define NOTE_F7 2794

#define NOTE_FS7 2960

#define NOTE_G7 3136

#define NOTE_GS7 3322

#define NOTE_A7 3520

#define NOTE_AS7 3729

#define NOTE_B7 3951

#define NOTE_C8 4186

#define NOTE_CS8 4435

#define NOTE_D8 4699

#define NOTE_DS8 4978

int melody[] = {
    NOTE_DS5,
    NOTE_E5,
    NOTE_FS5,
    0,
    NOTE_B5,
    NOTE_E5,
    NOTE_DS5,
    NOTE_E5,
    NOTE_FS5,
    NOTE_B5,
    NOTE_DS6,
    NOTE_E6,
    NOTE_DS6,
    NOTE_AS5,
    NOTE_B5,
    0,
    NOTE_FS5,
    0,
    NOTE_DS5,
    NOTE_E5,
    NOTE_FS5,
    0,
    NOTE_B5,
    NOTE_CS6,
    NOTE_AS5,
    NOTE_B5,
    NOTE_CS6,
    NOTE_E6,
    NOTE_DS6,
    NOTE_E6,
    NOTE_CS6,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_D4,
    NOTE_DS4,
    NOTE_FS2,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_D4,
    NOTE_DS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_D4,
    NOTE_DS4,
    NOTE_FS2,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_D4,
    NOTE_DS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_E3,
    NOTE_DS3,
    NOTE_E3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_AS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_AS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_E3,
    NOTE_DS3,
    NOTE_E3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_AS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_D4,
    NOTE_DS4,
    NOTE_FS2,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_D4,
    NOTE_DS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_D4,
    NOTE_DS4,
    NOTE_FS2,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_GS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_D4,
    NOTE_DS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_D4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_FS4,
    NOTE_CS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_CS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_E3,
    NOTE_DS3,
    NOTE_E3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_AS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_AS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_CS4,
    NOTE_B3,
    NOTE_E3,
    NOTE_DS3,
    NOTE_E3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_CS4,
    NOTE_DS4,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_FS3,
    NOTE_B3,
    NOTE_B3,
    NOTE_AS3,
    NOTE_B3,
    NOTE_FS3,
    NOTE_GS3,
    NOTE_B3,
    NOTE_E4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_FS4,
    NOTE_B3,
    NOTE_CS4,
};

// note durations: 4 = quarter note, 8 = eighth note, etc
int noteDurations[] = {
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    8,
    8,
};

void setup()
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++)
  {

    /*
      to calculate the note duration, take one second divided by the note type.
      e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     */
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
     */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(8); // stop the tone playing:
  }
  digitalWrite(8, LOW);
}

void loop() { /*press reset to replay. */ }