#pragma once

#include "math.h"
#include "vec.hpp"
#include <Arduino.h>
#include <cmath>
#include <cstdint>

struct Ahrs {

private:
  uint32_t last_update = 0;

public:
  Vec3<float> rotations;

  Ahrs() { this->rotations = {0.0f, 0.0f, 0.0f}; }
  // complementary filter
  void update(Vec3<float> &acc, Vec3<float> &gyro, Vec3<float> &mag) {

    const float dt = (millis() - this->last_update) / 1000.0f;

    Vec3<float> TempAngles = {0.0f, 0.0f, 0.0f};
    Vec3<float> gyroAngles = gyro * dt;
    Serial
        .print(gyroAngles.x)
        // Vec3<float> gyroAngles = {0.0f, 0.0f, 0.0f};

        TempAngles.x = atan2(acc.y, acc.z);
    TempAngles.y = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z));

    TempAngles.z = atan2(mag.z * sin(TempAngles.y) - mag.y * cos(TempAngles.y),
                         mag.x * cos(TempAngles.x) +
                             mag.y * sin(TempAngles.x) * sin(TempAngles.y) +
                             mag.z * sin(TempAngles.x) * cos(TempAngles.y));

    constexpr double gain = 0.98;

    rotations.x = (rotations.x + (gyroAngles.x / 180 * M_PI)) * gain +
                  TempAngles.x * (1.0 - gain);
    rotations.y = (rotations.y + (gyroAngles.y / 180 * M_PI)) * gain +
                  TempAngles.y * (1.0 - gain);
    rotations.z = (rotations.z + (gyroAngles.z / 180 * M_PI)) * gain +
                  TempAngles.z * (1.0 - gain);

    this->last_update = millis();
  }
};