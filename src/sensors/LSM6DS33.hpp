#ifndef LSM6DS33_HPP
#define LSM6DS33_HPP

/*
DATA SHEET:
https://pdf1.alldatasheet.com/datasheet-pdf/download/880694/STMICROELECTRONICS/LSM6DS33.html
*/

#include <LSM6.h>
#include "vec.hpp"

constexpr size_t CALIBRATION_SAMPLES = 500;

struct LSM6DS33
{
    enum class GyroScale : uint8_t
    {
        dps125,
        dps245,
        dps500,
        dps1000,
        dps2000,
    };

    enum class GyroRate : uint16_t
    {
        Hz13,
        Hz26,
        Hz52,
        Hz104,
        Hz208,
        Hz416,
        Hz833,
        Hz1660,

    };

    enum class AccelScale : uint8_t
    {
        g2,
        g16,
        g4,
        g8,
    };

    enum class AccelRate : uint16_t

    {
        off,
        Hz13,
        Hz26,
        Hz52,
        Hz104,
        Hz208,
        Hz416,
        Hz833,
        Hz1660,
        Hz3330,
        Hz6660,
    };

    Vec3<float> gyroOffset;
    Vec3<float> accelOffset;

    LSM6DS33();

    void configureGyro(GyroScale scale, GyroRate rate);
    void configureAccel(AccelScale scale, AccelRate rate);

    void calibrateGyro();
    void calibrateAccel();

    Vec3<float> readAccel();
    Vec3<float> readGyro();

private:
    LSM6 imu;

    // TODO:
    // read scale from registers
    GyroScale current_gyro_scale = GyroScale::dps245;
    AccelScale current_accel_scale = AccelScale::g2;
};

#endif