#include <Servo.h>
#include "recovery.hpp"
#include <Arduino.h>

Recovery::Recovery()
{
    this->servo.write(90);

    this->servo.attach(SERVO_PIN);
    Serial.println("Recovery initialized");
}
void Recovery::deploy()
{
    servo.write(0);
    delay(200);
    servo.write(90);
    delay(200);
    // this->servo.write(SERVO_ROTATION_ANGLE);
}