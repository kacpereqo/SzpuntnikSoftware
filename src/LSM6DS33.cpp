#include "LSM6DS33.hpp"
#include <LSM6.h>

LSM6DS33::LSM6DS33()
{
    if (!imu.init())
    {
        Serial.println("Failed to detect and initialize IMU!");
        while (1)
            ;
    }
    imu.enableDefault();
    configureAccel(AccelScale::g2, AccelRate::Hz1660);
    configureGyro(GyroScale::dps245, GyroRate::Hz1660);
}

void LSM6DS33::configureGyro(GyroScale scale, GyroRate rate)
{

    current_gyro_scale = scale;

    int8_t CTRL2_G_VALUE = 0x00;

    // if cause it is using 3 bits to store 5 values

    if (scale == GyroScale::dps125)
    {
        CTRL2_G_VALUE |= (int8_t)scale << 1;
    }
    else
    {
        CTRL2_G_VALUE |= (int8_t)scale << 2;
    }

    CTRL2_G_VALUE |= (int8_t)rate << 4;

    imu.writeReg(LSM6::CTRL2_G, CTRL2_G_VALUE);
}

void LSM6DS33::configureAccel(AccelScale scale, AccelRate rate)
{
    current_accel_scale = scale;

    uint8_t CTRL1_XL_VALUE = 0x00;

    CTRL1_XL_VALUE |= (uint8_t)scale << 2;
    CTRL1_XL_VALUE |= (uint8_t)rate << 4;

    imu.writeReg(LSM6::CTRL1_XL, CTRL1_XL_VALUE);
}

LSM6DS33::Data LSM6DS33::readAccel()
{
    imu.readAcc();

    uint8_t temp;
    switch (current_accel_scale)
    {
    case AccelScale::g2:
        temp = 0;
        break;
    case AccelScale::g4:
        temp = 1;
        break;
    case AccelScale::g8:
        temp = 2;
        break;
    case AccelScale::g16:
        temp = 3;
        break;
    }

    const float divide_factor = (1 << (14 - temp));

    return {
        imu.a.x / divide_factor,
        imu.a.y / divide_factor,
        imu.a.z / divide_factor};
}

LSM6DS33::Data LSM6DS33::readGyro()
{
    imu.readGyro();

    const float divide_factor = 245;

    return {
        imu.g.x / divide_factor,
        imu.g.y / divide_factor,
        imu.g.z / divide_factor};
}