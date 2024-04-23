#include <Servo.h>
#include "recovery.hpp"

Recovery::Recovery()
{
    this->servo.attach(SERVO_PIN);
}

void Recovery::deploy()
{
    this->servo.write(SERVO_ROTATION_ANGLE);
}