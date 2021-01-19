#pragma once

#ifndef LEAPP_MATH_HPP
#define LEAPP_MATH_HPP

#include <ostream>

namespace Leapp {

struct Vector {
  float x {};
  float y {};
  float z {};
};

static inline std::ostream& operator<<(std::ostream& stream, const Vector& vec) {
  stream << '[' << vec.x << "; " << vec.y << "; " << vec.z << ']';
  return stream;
}

struct Matrix {
  Vector rows[3] {};
};

static inline std::ostream& operator<<(std::ostream& stream, const Matrix& mat) {
  stream << '[' << mat.rows[0] << '\n'
         << ' ' << mat.rows[1] << '\n'
         << ' ' << mat.rows[2] << ']';
  return stream;
}

struct Quaternion {
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
