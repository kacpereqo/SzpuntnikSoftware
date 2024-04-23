#ifndef LIS3MDL_HPP
#define LIS3MDL_HPP

#include <LIS3MDL.h>
#include "vec.hpp"

struct Magnetometer
{
    enum class Scale : uint8_t
    {
        gauss4,
        gauss8,
        gauss12,
        gauss16,
    };

    Magnetometer();
    Vec3<int16_t> readMag();

private:
    LIS3MDL mag;
};

#endif // LIS3MDL_HPP
