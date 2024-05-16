#include "imu.hpp"

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

    for (size_t i = 0; i < 10; i++)
    {
        this->appendAccel();
    }
}

void Imu::calculateRollAndPitch()
{

    constexpr float GYRO_SENSITIVITY = 0.96;
    constexpr float ACCEL_SENSITIVITY = 0.04;

    // assert(ACCEL_SENSITIVITY + GYRO_SENSITIVITY == 1);

    static long lastUpdate = 0;

    double dt = (millis() - lastUpdate) / 1000.0;
    lastUpdate = millis();

    const float pitchAcc = atan2(accel.z, sqrt(accel.x * accel.x + accel.y * accel.y)) * RAD_TO_DEG;
    const float rollAcc = atan2(accel.x, sqrt(accel.y * accel.y + accel.z * accel.z)) * RAD_TO_DEG;
    const float yawAcc = atan2(accel.y, sqrt(accel.x * accel.x + accel.z * accel.z)) * RAD_TO_DEG;

    // this->pitch = lowPassFilter(pitchAcc * ACCEL_SENSITIVITY + (this->pitch + gyro.x * dt) * GYRO_SENSITIVITY, this->pitch, 0.1);
    // this->roll = lowPassFilter(rollAcc * ACCEL_SENSITIVITY + (this->roll + gyro.y * dt) * GYRO_SENSITIVITY, this->pitch, 0.1);

    this->pitch = pitchAcc * ACCEL_SENSITIVITY + (this->pitch + gyro.x * dt) * GYRO_SENSITIVITY;
    this->roll = rollAcc * ACCEL_SENSITIVITY + (this->roll + gyro.y * dt) * GYRO_SENSITIVITY;
    this->yaw = yawAcc * ACCEL_SENSITIVITY + (this->yaw + gyro.z * dt) * GYRO_SENSITIVITY;
}

void Imu::calculateYaw()
{

    constexpr float GYRO_SENSITIVITY = 0.00;
    constexpr float MAG_SENSIVITY = 1.00;

    // assert(MAG_SENSIVITY + GYRO_SENSITIVITY == 1);

    constexpr int16_t min_x = -1334;
    constexpr int16_t max_x = 4341;

    constexpr int16_t min_y = -6243;
    constexpr int16_t max_y = -781;

    constexpr int16_t min_z = 2767;
    constexpr int16_t max_z = 8140;

    constexpr float declinationAngle = 0.593; // in radians

    // normalize magnetometer values to [-1, 1]
    Vec2<float> normalized_mag = {
        (float)(mag.x * cos(roll * DEG_TO_RAD) - min_x) / (max_x - min_x) * 2 - 1,
        (float)(mag.y * cos(pitch * DEG_TO_RAD) - min_y) / (max_y - min_y) * 2 - 1,

    };

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
    this->accel = this->getAccel();
    this->gyro = this->imu.readGyro();
    this->preassure = this->barometer.readPressure();

    // calculateYaw();
    // calculateAlltitude();
    calculateRollAndPitch();
}

void Imu::readings()
{

    // ROTATION
    Serial.print("Pitch: ");
    Serial.print(this->pitch);
    Serial.print(",");

    Serial.print(" Roll: ");
    Serial.print(this->roll);
    Serial.print(",");

    Serial.print(" Yaw: ");
    Serial.print(this->yaw);
    // Serial.print(",");
    // Serial.print(180);
    // Serial.print(",");
    // Serial.print(-180);

    // Serial.print(" | ");
    // ACCELERATION
    // Serial.print(" Accel x: ");
    // Serial.print(this->accel.x);
    // Serial.print(" Accel y: ");
    // Serial.print(this->accel.y);
    // Serial.print(" Accel z: ");
    // Serial.print(this->accel.z);

    // end of line
    Serial.println();
}

void Imu::appendAccel()
{
    Vec3<float> accel = this->imu.readAccel();

    accelAvg[counter] = accel;
    counter = (counter + 1) % 10;
}

Vec3<float> Imu::getAccel()
{
    appendAccel();

    Vec3<float> accel = {0, 0, 0};

    for (size_t i = 0; i < 10; i++)
    {
        accel.x += accelAvg[i].x;
        accel.y += accelAvg[i].y;
        accel.z += accelAvg[i].z;
    }

    accel.x /= 10;
    accel.y /= 10;
    accel.z /= 10;

    float standardDeviation = 0;

    return {
        accel.x,
        accel.y,
        accel.z};
}