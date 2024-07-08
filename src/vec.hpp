#pragma once

template <typename T> struct Vec3 {
  T x;
  T y;
  T z;

  Vec3<T> operator+(const T &rhs) const { return {x + rhs, y + rhs, z + rhs}; }

  Vec3<T> operator+(const Vec3<T> &rhs) const {
    return {x - rhs.x, y - rhs.y, z - rhs.z};
  }

  Vec3<T> operator+=(const Vec3<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vec3<T> operator-(Vec3<T> &rhs) const {
    return {x - rhs.x, y - rhs.y, z - rhs.z};
  }

  operator float() const { return {x + y + z}; }

  Vec3<T> operator*(const T &rhs) const { return {x * rhs, y * rhs, z * rhs}; }

  template <typename U> Vec3<T> operator/(U &rhs) const {
    return {x / rhs, y / rhs, z / rhs};
  }

  Vec3<T> operator/(T &rhs) const { return {x / rhs, y / rhs, z / rhs}; }

  Vec3<T> operator/=(const T &rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }
};

template <typename T> struct Vec2 {
  T x;
  T y;
};
