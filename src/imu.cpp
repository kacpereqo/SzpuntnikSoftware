#include "Imu.hpp"

#include <Arduino.h>
#include "filters/lowpass.h"

Imu::Imu()
{
    imu.configureAccel(LSM6DS33::AccelScale::g16, LSM6DS33::AccelRate::Hz6660);
    imu.configureGyro(LSM6DS33::GyroScale::dps245, LSM6DS33::GyroRate::Hz1660);
}

void Imu::calibrate()
{
    imu.calibrateGyro();
}

void Imu::calculateRollAndPitch()
{

    constexpr float GYRO_SENSITIVITY = 0.98;
    constexpr float ACCEL_SENSITIVITY = 0.02;

    // assert(ACCEL_SENSITIVITY + GYRO_SENSITIVITY == 1);

    static long lastUpdate = 0;

    double dt = (millis() - lastUpdate) / 1000.0;
    lastUpdate = millis();

    const float pitchAcc = atan2(accel.y, sqrt(accel.x * accel.x + accel.z * accel.z)) * RAD_TO_DEG;
    const float rollAcc = atan2(accel.x, sqrt(accel.y * accel.y + accel.z * accel.z)) * RAD_TO_DEG;

    // this->pitch = lowPassFilter(pitchAcc * ACCEL_SENSITIVITY + (this->pitch + gyro.x * dt) * GYRO_SENSITIVITY, this->pitch, 0.1);
    // this->roll = lowPassFilter(rollAcc * ACCEL_SENSITIVITY + (this->roll + gyro.y * dt) * GYRO_SENSITIVITY, this->pitch, 0.1);

    this->pitch = pitchAcc * ACCEL_SENSITIVITY + (this->pitch + gyro.x * dt) * GYRO_SENSITIVITY;
    this->roll = rollAcc * ACCEL_SENSITIVITY + (this->roll + gyro.y * dt) * GYRO_SENSITIVITY;
}

void Imu::calculateYaw()
{

    constexpr float GYRO_SENSITIVITY = 0.00;
    constexpr float MAG_SENSIVITY = 1.00;

    // assert(MAG_SENSIVITY + GYRO_SENSITIVITY == 1);

    constexpr int16_t min_x = -973;
    constexpr int16_t max_x = 5355;

    constexpr int16_t min_y = -5746;
    constexpr int16_t max_y = -3041;

    constexpr int16_t min_z = 3236;
    constexpr int16_t max_z = 8727;

    constexpr float declinationAngle = 0.593; // in radians

    // normalize magnetometer values to [-1, 1]
    Vec2<float> normalized_mag = {
        (float)(mag.x * cos(roll * DEG_TO_RAD) - min_x) / (max_x - min_x) * 2 - 1,
        (float)(mag.y * cos(pitch * DEG_TO_RAD) - min_y) / (max_y - min_y) * 2 - 1,

    };
    // Serial.print(.x);
    // Serial.print(",");
    // Serial.print(mag.y);
    // Serial.print(",");

    Vec2<float> normalized_mag_z = {
        (float)(mag.z * sin(pitch * DEG_TO_RAD) - min_z) / (max_z - min_z) * 2 - 1,
        (float)(mag.z * sin(roll * DEG_TO_RAD) - min_z) / (max_z - min_z) * 2 - 1};

    const float heading = atan2(normalized_mag.y, normalized_mag.x) + declinationAngle;
    const float headingDegrees = heading * RAD_TO_DEG;

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

void Imu::readings()
{

    Serial.print(this->pitch);
    Serial.print(",");
    // Serial.print(this->yaw);
    Serial.print(0);
    Serial.print(",");
    Serial.print(this->roll);
    Serial.println();
    // Serial.print(this->accel.x);
    // Serial.print(",");
    // Serial.print(this->accel.y);
    // Serial.print(",");
    // Serial.print(this->accel.z);
    // Serial.print(",");
    // Serial.print(",");
    // Serial.print(" Preassure: ");
    // Serial.println(this->preassure);
    // delay(1000);
}