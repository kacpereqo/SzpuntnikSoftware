#include "recovery.hpp"
#include "Arduino.h"
#include "utils/constants.hpp"

Recovery::Recovery()
{
    this->servo.attach(RECOVERY_SERVO_PIN);
    if (!this->servo.attached())
    {
        Serial.println("Servo not attached");
        while (1)
            ;
    }
    this->servo.write(0);
    Serial.println("Recovery system initialized");
}

void Recovery::test()
{
    Serial.println("Testing recovery system");
    for (int pos = 0; pos <= 180; pos += 1)
    {                           // goes from 0 degrees to 180 degrees
        this->servo.write(pos); // tell servo to go to position in variable 'pos'
        delay(15);              // waits 15 ms for the servo to reach the position
    }
    for (int pos = 180; pos >= 0; pos -= 1)
    {                           // goes from 180 degrees to 0 degrees
        this->servo.write(pos); // tell servo to go to position in variable 'pos'
        delay(15);              // waits 15 ms for the servo to reach the position
    }
}

void Recovery::deploy(TriggeredBy trigger)
{
    ;
}