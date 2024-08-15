#include "innerBarometer.hpp"
#include "utils/singletons.hpp"

InnerBarometer::InnerBarometer() : sensor(getLPS())
{
    this->sensor = getLPS();

    this->sensor.enableDefault();
}

void InnerBarometer::configure()
{
    this->sensor.enableDefault();
}

float InnerBarometer::getData()
{
    this->data = this->sensor.readPressureMillibars();
    return this->data;
}

float InnerBarometer::getDataInMeters()
{
    return this->sensor.pressureToAltitudeMeters(this->getData());
}