#include "magnetometer.hpp"
#include <LIS3MDL.h>
#include <LSM6.h>

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
    Data data = this->readNormalizeData();

    float heading = atan2(data.y, data.x);
    constexpr float declinationAngle = 0.22;
    heading += declinationAngle;

    float headingDegrees = heading * 180 / M_PI;

    Serial.print("Heading: ");
    Serial.println(headingDegrees);
}

Magnetometer::Data Magnetometer::readNormalizeData()
{
    mag.read();

    // calibration values
    constexpr int16_t min_x = -973;
    constexpr int16_t max_x = 5355;

    constexpr int16_t min_y = -5746;
    constexpr int16_t max_y = -3041;

    constexpr int16_t min_z = 3236;
    constexpr int16_t max_z = 8727;

    float x = mag.m.x;
    float y = mag.m.y;
    float z = mag.m.z;

    x = (x - min_x) / (max_x - min_x) * 2 - 1;
    y = (y - min_y) / (max_y - min_y) * 2 - 1;
    z = (z - min_z) / (max_z - min_z) * 2 - 1;

    return {x, y, z};
}