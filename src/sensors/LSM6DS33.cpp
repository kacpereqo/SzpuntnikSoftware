#include "LSM6DS33.hpp"
#include <LSM6.h>
LSM6DS33::LSM6DS33()
{
    if (!imu.init())
    {
        // Serial.println("Failed to detect and initialize IMU!");
        while (1)
            ;
    }
    imu.enableDefault();
    // Serial.println("IMU initialized");

    calibrateGyro();
}

void LSM6DS33::calibrateGyro()
{
    // Serial.println("Calibrating Gyro...");

    Vec3<float> data = {0, 0, 0};

    for (size_t i = 0; i < CALIBRATION_SAMPLES; i++)
    {
        Vec3<float> gyro = this->readGyro();

        data.x += gyro.x;
        data.y += gyro.y;
        data.z += gyro.z;

        // delay(1);
    }

    // Serial.println("Calibration done");

    gyroOffset.x = data.x / CALIBRATION_SAMPLES;
    gyroOffset.y = data.y / CALIBRATION_SAMPLES;
    gyroOffset.z = data.z / CALIBRATION_SAMPLES;
}

void LSM6DS33::calibrateAccel()
{
    // Serial.println("Calibrating Accel...");

    Vec3<float> data = {0, 0, 0};

    for (size_t i = 0; i < CALIBRATION_SAMPLES; i++)
    {
        Vec3<float> accel = this->readAccel();

        data.x += accel.x;
        data.y += accel.y;
        data.z += accel.z;

        // delay(1);
    }

    // Serial.println("Calibration done");

    accelOffset.x = data.x / CALIBRATION_SAMPLES;
    accelOffset.y = data.y / CALIBRATION_SAMPLES;
    accelOffset.z = data.z / CALIBRATION_SAMPLES;
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
    CTRL1_XL_VALUE |= (uint8_t)0;

    imu.writeReg(LSM6::CTRL1_XL, CTRL1_XL_VALUE);
}

Vec3<float> LSM6DS33::readAccel()
{
    imu.readAcc();

    uint8_t scale;
    switch (current_accel_scale)
    {
    case AccelScale::g2:
        scale = 0;
        break;
    case AccelScale::g4:
        scale = 1;
        break;
    case AccelScale::g8:
        scale = 2;
        break;
    case AccelScale::g16:
        scale = 3;
        break;
    }

    const float divide_factor = (1 << (14 - scale));

    return {
        imu.a.y / divide_factor - accelOffset.y,
        -imu.a.x / divide_factor - accelOffset.x,
        imu.a.z / divide_factor - accelOffset.z,
    };
}

Vec3<float> LSM6DS33::readGyro()
{
    imu.readGyro();

    constexpr float divide_factor = 245;

    return {
        imu.g.y / divide_factor - gyroOffset.y,
        -imu.g.x / divide_factor - gyroOffset.x,
        imu.g.z / divide_factor - gyroOffset.z,
    };
}

Vec3<int16_t> LSM6DS33::readRawAccel()
{
    imu.readAcc();

    return {
        imu.a.y,
        imu.a.x,
        imu.a.z,
    };
}

Vec3<int16_t> LSM6DS33::readRawGyro()
{
    imu.readGyro();

    return {
        imu.g.y,
        imu.g.x,
        imu.g.z,
    };
}