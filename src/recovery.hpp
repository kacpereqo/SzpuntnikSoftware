#ifndef RECOVERY_HPP
#define RECOVERY_HPP

constexpr int8_t SERVO_PIN = 10;
constexpr int8_t SERVO_ROTATION_ANGLE = 90;

struct Recovery
{
    Recovery();

    void deploy();

private:
    Servo servo;
};

#endif // RECOVERY_HPP