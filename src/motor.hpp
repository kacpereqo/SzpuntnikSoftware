#pragma once

constexpr unsigned short SERVO_PIN = 10;
constexpr unsigned short SERVO_ROTATION_ANGLE = 90;

void motor_init();
void motor_loop();
void rotate(int angle);