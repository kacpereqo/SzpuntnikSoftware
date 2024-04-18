#include "magnetometer.hpp"

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

    const float scale = 16;

    return {
        mag.m.x / scale,
        mag.m.y / scale,
        mag.m.z / scale,
    };
}

void Magnetometer::compass()
{

    float headingRadians = atan2(mag.m.y, mag.m.x);
    float headingDegrees = headingRadians * 180 / PI;
    float declinationAngle = 11.41666666666667;

    headingDegrees += declinationAngle;

    if (headingDegrees < 0)
    {
        headingDegrees += 360;
    }

    Serial.print("Heading: ");
    Serial.print(headingDegrees);
    Serial.print(", ");

    if (headingDegrees > 348.75 || headingDegrees < 11.25)
    {
        Serial.print(" N");
    }
    else if (headingDegrees > 11.25 && headingDegrees < 33.75)
    {
        Serial.print(" NNE");
    }
    else if (headingDegrees > 33.75 && headingDegrees < 56.25)
    {
        Serial.print(" NE");
    }
    else if (headingDegrees > 56.25 && headingDegrees < 78.75)
    {
        Serial.print(" ENE");
    }
    else if (headingDegrees > 78.75 && headingDegrees < 101.25)
    {
        Serial.print(" E");
    }
    else if (headingDegrees > 101.25 && headingDegrees < 123.75)
    {
        Serial.print(" ESE");
    }
    else if (headingDegrees > 123.75 && headingDegrees < 146.25)
    {
        Serial.print(" SE");
    }
    else if (headingDegrees > 146.25 && headingDegrees < 168.75)
    {
        Serial.print(" SSE");
    }
    else if (headingDegrees > 168.75 && headingDegrees < 191.25)
    {
        Serial.print(" S");
    }
    else if (headingDegrees > 191.25 && headingDegrees < 213.75)
    {
        Serial.print(" SSW");
    }
    else if (headingDegrees > 213.75 && headingDegrees < 236.25)
    {
        Serial.print(" SW");
    }
    else if (headingDegrees > 236.25 && headingDegrees < 258.75)
    {
        Serial.print(" WSW");
    }
    else if (headingDegrees > 258.75 && headingDegrees < 281.25)
    {
        Serial.print(" W");
    }
    else if (headingDegrees > 281.25 && headingDegrees < 303.75)
    {
        Serial.print(" WNW");
    }
    else if (headingDegrees > 303.75 && headingDegrees < 326.25)
    {
        Serial.print(" NW");
    }
    else if (headingDegrees > 326.25 && headingDegrees < 348.75)
    {
        Serial.print(" NNW");
    }
    Serial.println();
}