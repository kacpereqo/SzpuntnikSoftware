
#include "LPS25H.hpp"

LPS25H::LPS25H()
{
    Serial.println("Initializing pressure sensor...");
    if (!ps.init())
    {
        Serial.println("Failed to autodetect pressure sensor!");
        while (1)
            ;
    }

    ps.enableDefault();
    Serial.println("Pressure sensor initialized");
}

float LPS25H::readPressure()
{
    return ps.readPressureMillibars();
}

float LPS25H::readAlltitude(float pressure)
{
    // TODO:
    // setting the sea level pressure to 1013.25 hPa is a temporary solution
    // this should obtained during the calibration process
    return ps.pressureToAltitudeMeters(pressure, 1013.25);
}

float LPS25H::readTemperature()
{
    return ps.readTemperatureC();
}