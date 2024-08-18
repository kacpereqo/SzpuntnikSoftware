#pragma once

class Ahrs
{
private:
  uint32_t last_update;
  float dt;
  float alpha;

  void calculatePitch(Vec3<float> &acc, Vec3<float> &gyro);
  void calculateRoll(Vec3<float> &acc, Vec3<float> &gyro);
  void calculateYaw(Vec3<float> &acc, Vec3<float> &mag, Vec3<float> &gyro);

public:
  Vec3<float> rotations;

  Ahrs();
  void update(Vec3<float> &acc, Vec3<float> &gyro, Vec3<float> &mag);
};