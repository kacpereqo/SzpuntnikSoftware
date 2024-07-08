#pragma once

#include "vec.hpp"
#include <cmath>

struct Ahrs {
  Vec3<float> rotations;

  // complementary filter
  void update(Vec3<float> &acc, Vec3<float> &gyro, Vec3<float> &mag) {
    Vec3<float> angles = {0.0f, 0.0f, 0.0f};

    Vec3<float> TempAngles = {0.0f, 0.0f, 0.0f};

    TempAngles.x = atan2(acc.y, acc.z);
    TempAngles.y = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z));

    TempAngles.z =
        atan2(mag.z * sin(TempAngles.y) - mag.y * cos(TempAngles.y),
              mag.x * cos(TempAngles.x) +
                  mag.y * sin(TempAngles.x * M_PI) * sin(TempAngles.y * M_PI) +
                  mag.z * sin(TempAngles.x * M_PI) * cos(TempAngles.y * M_PI));

    constexpr double gain = 0.98;

    angles.x = angles.x * gain + TempAngles.x * (1.0 - gain);
    angles.y = angles.y * gain + TempAngles.y * (1.0 - gain);
    angles.z = angles.z * gain + TempAngles.z * (1.0 - gain);
  }
};