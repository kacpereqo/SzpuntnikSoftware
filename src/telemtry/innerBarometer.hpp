#pragma once

#include <EnvironmentCalculations.h>
#include <BME280I2C.h>
#include <Wire.h>

class InnerBarometer
{
public:
    float referencePressure = 1013.15f;
    float outdoorTemp = 15.0f;
    float barometerAltitude = 0.0f;

    float pressure;
    float temperature;
    float humidity;
    float altitude;

    float initAltitude;

    const BME280::TempUnit temperatureUnit = (BME280::TempUnit_Celsius);
    const BME280::PresUnit pressureUnit = (BME280::PresUnit_hPa);

    BME280I2C bme;

    InnerBarometer()
    {
        BME280I2C::Settings settings(
            BME280::OSR_X1,
            BME280::OSR_X1,
            BME280::OSR_X1,
            BME280::Mode_Forced,
            BME280::StandbyTime_1000ms,
            BME280::Filter_16,
            BME280::SpiEnable_False,
            BME280I2C::I2CAddr_0x76);

        this->bme = BME280I2C(settings);

        if (!bme.begin())
        {
            Serial.println("Could not find a valid BME280 sensor, check wiring!");
            while (1)
                ;
        }

        this->initAltitude = 0.0f;
        float tempAltitude = 0;

        getData();
        delay(100);

        for (size_t i = 0; i < 10; i++)
        {
            getData();
            tempAltitude += this->altitude / 10.0f;
        }

        this->initAltitude = tempAltitude;
    }

    void getData()
    {
        bme.read(this->pressure, this->temperature, this->humidity, this->temperatureUnit, this->pressureUnit);
        this->altitude = getAltitude() - this->initAltitude;
    }

    float getAltitude()
    {
        return EnvironmentCalculations::Altitude(this->pressure, EnvironmentCalculations::AltitudeUnit::AltitudeUnit_Meters, this->referencePressure, this->outdoorTemp, EnvironmentCalculations::TempUnit::TempUnit_Celsius);
    }
};