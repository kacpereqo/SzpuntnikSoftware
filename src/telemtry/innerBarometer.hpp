#pragma once

#include <EnvironmentCalculations.h>
#include <BME280I2C.h>
#include <Wire.h>

class InnerBarometer
{
public:
    float referencePressure = 1018.6;
    float outdoorTemp = 4.7;
    float barometerAltitude = 1650.3;
    float pres, temp, hum;
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
    }

    float getDataInMeters()
    {

        BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
        BME280::PresUnit presUnit(BME280::PresUnit_hPa);

        bme.read(this->pres, this->temp, this->hum, tempUnit, presUnit);

        return this->pres;
    }
};