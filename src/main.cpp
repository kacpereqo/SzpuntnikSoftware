#include <Arduino.h>

#include "gy-521.hpp"
#include "motor.hpp"

constexpr unsigned short BUTTON_PIN = D2;

void setup(void)
{
    Serial.begin(115200);
    mpu_init();
    motor_init();
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
    mpu_loop();
}