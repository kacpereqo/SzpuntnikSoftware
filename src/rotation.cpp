#include "rotation.hpp"
#include "macros.hpp"
#include <Arduino.h>

long current = 0;
long lastUpdate = 0;

Rotation::Rotation()
{
    imu.configureAccel(LSM6DS33::AccelScale::g2, LSM6DS33::AccelRate::Hz1660);
    imu.configureGyro(LSM6DS33::GyroScale::dps245, LSM6DS33::GyroRate::Hz1660);
}

void Rotation::complementaryFilter()
{
    Data accel = imu.readAccel();
    Data gyro = imu.readGyro();

    float dt = (millis() - lastUpdate) / 1000.0;
    lastUpdate = millis();

    float pitchAcc = atan2(accel.y, sqrt(accel.x * accel.x + accel.z * accel.z)) * RAD_TO_DEG;
    float rollAcc = atan2(accel.x, sqrt(accel.y * accel.y + accel.z * accel.z)) * RAD_TO_DEG;

    x = 0.95 * (x + gyro.x * dt) + 0.05 * pitchAcc;
    y = 0.95 * (y + gyro.y * dt) + 0.05 * rollAcc;
    z = gyro.z;
}

void Rotation::updateRotation()
{

#ifdef ROTATION_DEBUG
    Serial.print(x);
    Serial.print(",");

    Serial.print(y);
    Serial.print(",");

    Serial.print(z);
    Serial.print(",");

    Serial.println();

    complementaryFilter();

#endif
}