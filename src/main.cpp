#include "gy-521.hpp"
#include <Arduino.h>

void setup(void)
{
    Serial.begin(115200);
    mpu_init();
}

void loop()
{

    mpu_loop();
}