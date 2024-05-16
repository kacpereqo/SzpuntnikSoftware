#ifndef RECOVERY_HPP
#define RECOVERY_HPP

#include <Servo.h>

constexpr int8_t SERVO_PIN = 5;
constexpr int8_t SERVO_ROTATION_ANGLE = 90;

struct Recovery
{
    Recovery();

    void deploy();

private:
    Servo servo;
};

#endif // RECOVERY_HPP