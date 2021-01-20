#pragma once

#ifndef LEAPP_MATH_HPP
#define LEAPP_MATH_HPP

#include <ostream>

struct _LEAP_VECTOR;
using LEAP_VECTOR = _LEAP_VECTOR;

struct _LEAP_MATRIX_3x3;
using LEAP_MATRIX_3x3 = _LEAP_MATRIX_3x3;

struct _LEAP_QUATERNION;
using LEAP_QUATERNION = _LEAP_QUATERNION;

namespace Leapp {

struct Vector {
  constexpr Vector() = default;
  Vector(const LEAP_VECTOR& vec) noexcept;

  float x {};
  float y {};
  float z {};
};

static inline std::ostream& operator<<(std::ostream& stream, const Vector& vec) {
  stream << '[' << vec.x << "; " << vec.y << "; " << vec.z << ']';
  return stream;
}

struct Matrix {
  constexpr Matrix() = default;
  Matrix(const LEAP_MATRIX_3x3& mat) noexcept;

  Vector rows[3] {};
};

static inline std::ostream& operator<<(std::ostream& stream, const Matrix& mat) {
  stream << '[' << mat.rows[0] << '\n'
         << ' ' << mat.rows[1] << '\n'
         << ' ' << mat.rows[2] << ']';
  return stream;
}

struct Quaternion {
  constexpr Quaternion() = default;
  Quaternion(const LEAP_QUATERNION& quat) noexcept;

  float x {};
  float y {};
  float z {};
  float w {};
};

static inline std::ostream& operator<<(std::ostream& stream, const Quaternion& quat) {
  stream << '[' << quat.x << "; " << quat.y << "; " << quat.z << "; " << quat.w << ']';
  return stream;
}

} // namespace Leapp

#endif // LEAPP_MATH_HPP
