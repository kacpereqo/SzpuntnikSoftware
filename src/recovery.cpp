#include <Servo.h>
#include "recovery.hpp"
#include <Arduino.h>

Recovery::Recovery()
{
    this->servo.write(0);
    this->servo.attach(SERVO_PIN);
    // Serial.println("Recovery initialized");
}
void Recovery::deploy()
{
    if (this->servo.read() == 0)
    {
        this->servo.write(180);
    }
}

void Recovery::open()
{
    if (this->servo.read() == 180)
    {
        this->servo.write(0);
    }
}