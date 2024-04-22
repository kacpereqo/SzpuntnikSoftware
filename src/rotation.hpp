#ifndef ROTATION_HPP
#define ROTATION_HPP

#include "sensors/LSM6DS33.hpp"

struct Rotation
{
    float x = 0;
    float y = 0;
    float z = 0;

    void updateRotation();

    Rotation();

private:
    LSM6DS33 imu;

    void complementaryFilter();
};

#endif

/*

    yaw
     | y
     |
     |
     |          x
    /------------ pitch
   /
  /
 /  z
roll

*/