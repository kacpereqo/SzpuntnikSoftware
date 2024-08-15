#include "sensor.hpp"
#include "vec.hpp"

class Thermometer : public Sensor
{
    Thermometer();

    void configure() override;
    float getData() override;
}