
#include "LPS25H.hpp"

constexpr size_t CALIBRATION_SAMPLES = 500;

LPS25H::LPS25H()
{
    Serial.println("Initializing pressure sensor...");
    if (!barometer.init())
    {
        Serial.println("Failed to autodetect pressure sensor!");
        while (1)
            ;
    }

    barometer.enableDefault();
    this->calibrateBarometer();

    Serial.println("Pressure sensor initialized");
}

void LPS25H::calibrateBarometer()
{
    Serial.println("Calibrating barometer...");

    for (size_t i = 0; i < CALIBRATION_SAMPLES; i++)
    {
        this->startPreassure += barometer.readPressureMillibars();

        // delay(1);
    }

    Serial.println("Calibration done");

    this->startPreassure /= CALIBRATION_SAMPLES;
}

float LPS25H::readPressure()
{
    return barometer.readPressureMillibars();
}

float LPS25H::readAlltitude(float pressure)
{
    return barometer.pressureToAltitudeMeters(pressure, 1019);
}

float LPS25H::readTemperature()
{
    return barometer.readTemperatureC();
}