#pragma once

#include "math.h"
#include "vec.hpp"
#include <Arduino.h>
#include <cmath>
#include <cstdint>

struct Ahrs
{

private:
  uint32_t last_update = 0;
  float dt = 0.0f;
  const float alpha = 0.97;

  void calculatePitch(Vec3<float> &acc, Vec3<float> &gyro)
  {
    const float pitch_gyro = (gyro.x * dt) * DEG_TO_RAD;
    const float pitch_acc = atan2(acc.y, sqrt(acc.x * acc.x + acc.z * acc.z));

    this->rotations.x = this->alpha * (this->rotations.x + pitch_gyro) +
                        (1 - this->alpha) * pitch_acc;
  }

  void calculateRoll(Vec3<float> &acc, Vec3<float> &gyro)
  {
    const float roll_gyro = gyro.y * dt / (180.0f * M_PI);
    const float roll_acc = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z));

    this->rotations.y = this->alpha * (this->rotations.y + roll_gyro) +
                        (1 - this->alpha) * roll_acc;
  }

  void calculateYaw(Vec3<float> &acc, Vec3<float> &mag, Vec3<float> &gyro)
  {

    const float yaw_gyro = (gyro.z * dt) / (180.0f * M_PI);
    const float yaw_acc = atan2(mag.y, mag.x);
    constexpr float declination = 6.94f / 180.0f * M_PI;

    this->rotations.z = this->alpha * (this->rotations.z + yaw_gyro) +
                        (1 - this->alpha) * yaw_acc + declination;
  }

public:
  Vec3<float> rotations;

  Ahrs() { this->rotations = {0.0f, 0.0f, 0.0f}; }
  // complementary filter
  void update(Vec3<float> &acc, Vec3<float> &gyro, Vec3<float> &mag)
  {

    this->dt = (millis() - this->last_update) / 1000.0f;

    this->calculatePitch(acc, gyro);
    this->calculateRoll(acc, gyro);
    this->calculateYaw(acc, mag, gyro);

    this->last_update = millis();
  }
};