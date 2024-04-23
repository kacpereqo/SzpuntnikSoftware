#ifndef ROTATION_HPP
#define ROTATION_HPP

#include "sensors/LSM6DS33.hpp"
#include "sensors/LPS25H.hpp"
#include "sensors/magnetometer.hpp"

struct Imu
{
    float pitch = 0;
    float yaw = 0;
    float roll = 0;
    float preassure = 0;
    float altitude = 0;

    void update();
    Imu();

private:
    LSM6DS33 imu;              // Accelerometer and Gyroscope
    LPS25H barometer;          // Barometer
    Magnetometer magnetometer; // Magnetometer

    // sensor readings
    Vec3<float> accel{};
    Vec3<float> gyro{};
    Vec3<int16_t> mag{};

    void calculateRollAndPitch();
    void calculateYaw();
    void calculateAlltitude();
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