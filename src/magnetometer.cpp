#include "magnetometer.hpp"
#include <vector>

Magnetometer::Magnetometer()
{
    if (!mag.init())
    {
        Serial.println("Failed to detect and initialize magnetometer!");
        while (1)
            ;
    }
    mag.enableDefault();
}

Magnetometer::Data Magnetometer::readMag()
{
    mag.read();

    return {
        mag.m.x,
        mag.m.y,
        mag.m.z,
    };
}

void Magnetometer::compass()
{
}