#pragma once

#include "math.h"
#include "vec.hpp"
#include <Arduino.h>
#include <cmath>
#include <cstdint>
#include "ahrs.hpp"

void Ahrs::calculatePitch(Vec3<float> &acc, Vec3<float> &gyro)
{
    const float pitch_gyro = (gyro.x * this->dt);
    const float pitch_acc = atan2(acc.y, sqrt(acc.x * acc.x + acc.z * acc.z)) * RAD_TO_DEG;

    this->rotations.x = this->alpha * (this->rotations.x + pitch_gyro) +
                        (1 - this->alpha) * pitch_acc;
}

void Ahrs::calculateRoll(Vec3<float> &acc, Vec3<float> &gyro)
{
    const float roll_gyro = gyro.y * this->dt;
    const float roll_acc = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z)) * RAD_TO_DEG;

    this->rotations.y = this->alpha * (this->rotations.y + roll_gyro) +
                        (1 - this->alpha) * roll_acc;
}

void Ahrs::calculateYaw(Vec3<float> &acc, Vec3<float> &mag, Vec3<float> &gyro)
{

    const float yaw_gyro = (gyro.z * this->dt);
    const float yaw_acc = atan2(mag.y, mag.x);
    constexpr float declination = 6.94f;

    this->rotations.z = this->alpha * (this->rotations.z + yaw_gyro) +
                        (1 - this->alpha) * yaw_acc + declination;
}

Ahrs::Ahrs()
{
    this->last_update = 0;
    this->dt = 0.0f;
    this->alpha = 0.97;
    this->rotations = {0.0f, 0.0f, 0.0f};
}
// complementary filter
void Ahrs::update(Vec3<float> &acc, Vec3<float> &gyro, Vec3<float> &mag)
{

    this->dt = (millis() - this->last_update) / 1000.0f;

    this->calculatePitch(acc, gyro);
    this->calculateRoll(acc, gyro);
    this->calculateYaw(acc, mag, gyro);

    this->last_update = millis();
}