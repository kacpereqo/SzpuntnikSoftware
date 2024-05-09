#include "magnetometer.hpp"
#include <LIS3MDL.h>
#include <LSM6.h>

Magnetometer::Magnetometer()
{
    Serial.println("Initializing magnetometer...");
    if (!mag.init())
    {
        Serial.println("Failed to detect and initialize magnetometer!");
        while (1)
            ;
    }
    mag.enableDefault();
    Serial.println("Magnetometer initialized");
}

Vec3<int16_t> Magnetometer::readMag()
{
    mag.read();

    return {
        mag.m.y,
        mag.m.z,
        mag.m.x,
    };
}
