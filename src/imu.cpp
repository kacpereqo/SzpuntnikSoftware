#include "Imu.hpp"
#include "macros.hpp"
#include <Arduino.h>

Imu::Imu()
{
    imu.configureAccel(LSM6DS33::AccelScale::g16, LSM6DS33::AccelRate::Hz6660);
    imu.configureGyro(LSM6DS33::GyroScale::dps245, LSM6DS33::GyroRate::Hz1660);
}

void Imu::calculateRollAndPitch()
{

    constexpr float GYRO_SENSITIVITY = 0.92;
    constexpr float ACCEL_SENSITIVITY = 0.08;

    // assert(ACCEL_SENSITIVITY + GYRO_SENSITIVITY == 1);

    static long lastUpdate = 0;

    float dt = (millis() - lastUpdate) / 1000.0;
    lastUpdate = millis();

    const float pitchAcc = atan2(accel.y, sqrt(accel.x * accel.x + accel.z * accel.z)) * RAD_TO_DEG;
    const float rollAcc = atan2(accel.x, sqrt(accel.y * accel.y + accel.z * accel.z)) * RAD_TO_DEG;

    this->pitch = pitchAcc * ACCEL_SENSITIVITY + (this->pitch + gyro.x * dt) * GYRO_SENSITIVITY;
    this->roll = rollAcc * ACCEL_SENSITIVITY + (this->roll + gyro.y * dt) * GYRO_SENSITIVITY;
}

void Imu::calculateYaw()
{

    constexpr float GYRO_SENSITIVITY = 0.08;
    constexpr float MAG_SENSIVITY = 0.92;

    // assert(MAG_SENSIVITY + GYRO_SENSITIVITY == 1);

    constexpr int16_t min_x = -973;
    constexpr int16_t max_x = 5355;

    constexpr int16_t min_y = -5746;
    constexpr int16_t max_y = -3041;

    constexpr int16_t min_z = 3236;
    constexpr int16_t max_z = 8727;

    constexpr float declinationAngle = 0.593; // in radians

    // normalize magnetometer values to [-1, 1]
    Vec3<float> normalized_mag = {
        (float)(mag.x * sin(pitch * DEG_TO_RAD) - min_x) / (max_x - min_x) * 2 - 1,
        (float)(mag.y * sin(roll * DEG_TO_RAD) - min_y) / (max_y - min_y) * 2 - 1,
    };

    const float heading = atan2(normalized_mag.y, normalized_mag.x) + declinationAngle;
    const float headingDegrees(heading * RAD_TO_DEG);

    this->yaw = headingDegrees * MAG_SENSIVITY + gyro.z * GYRO_SENSITIVITY;
}

void Imu::calculateAlltitude()
{
    this->altitude = this->barometer.readAlltitude(this->preassure);
}

void Imu::update()
{
    this->mag = this->magnetometer.readMag();
    this->accel = this->imu.readAccel();
    this->gyro = this->imu.readGyro();
    this->preassure = this->barometer.readPressure();

    calculateYaw();
    calculateAlltitude();
    calculateRollAndPitch();
}