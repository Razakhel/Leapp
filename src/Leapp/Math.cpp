#include "Leapp/Math.hpp"
#include "Leapp/Leapp.hpp"

namespace Leapp {

Vector::Vector(const LEAP_VECTOR& vec) noexcept : x{ vec.x }, y{ vec.y }, z{ vec.z } {}

Matrix::Matrix(const LEAP_MATRIX_3x3& mat) noexcept : rows{ mat.m[0], mat.m[1], mat.m[2] } {}

Quaternion::Quaternion(const LEAP_QUATERNION& quat) noexcept : x{ quat.x }, y{ quat.y }, z{ quat.z }, w{ quat.w } {}

}
