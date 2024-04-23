#ifndef LIS3MDL_HPP
#define LIS3MDL_HPP

#include <LIS3MDL.h>
#include "vec3.hpp"

struct Magnetometer
{
    enum class Scale : uint8_t
    {
        gauss4,
        gauss8,
        gauss12,
        gauss16,
    };

    struct Data
    {
        float x;
        float y;
        float z;
    };

    Magnetometer();
    Vec3 readMag();

private:
    LIS3MDL mag;
};

#endif // LIS3MDL_HPP
