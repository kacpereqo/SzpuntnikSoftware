
#include "LPS25H.hpp"

LPS25H::LPS25H()
{
    if (!ps.init())
    {
        Serial.println("Failed to autodetect pressure sensor!");
        while (1)
            ;
    }

    ps.enableDefault();
}

LPS25H::Data LPS25H::readPressure()
{
    return ps.readPressureMillibars();
}

LPS25H::Data LPS25H::readAltitude()
{
    return ps.pressureToAltitudeMeters(ps.readPressureMillibars());
}

LPS25H::Data LPS25H::readTemperature()
{
    return ps.readTemperatureC();
}