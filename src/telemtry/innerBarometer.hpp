#pragma once

#include "vec.hpp"
#include "sensor.hpp"
#include <LPS.h>

class InnerBarometer
{
private:
    int16_t offset_raw;
    int16_t raw;
    float data;
    LPS &sensor;

public:
    InnerBarometer();
    void configure();
    void calibrate();

    float getData();
    float getDataInMeters();
    int16_t &getRawData();
};