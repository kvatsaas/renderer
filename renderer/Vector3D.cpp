#include "Vector3D.h"
#include <stdexcept>

namespace renderer {

Vector3D::Vector3D()
  : x(0), y(x), z(x) {}

Vector3D::Vector3D(float a, float b, float c)
  : x(a), y(b), z(c) {}

Vector3D::Vector3D(const Vector3D &v)
  : x(v.x), y(v.y), z(v.z) {}

Vector3D Vector3D::scale(const float scalar) const
{
  return Vector3D(x * scalar, y * scalar, z * scalar);
}

const float Vector3D::operator[](const int index) const{
  switch (index) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  default:
    throw std::out_of_range("Vector3D index range is 0-2");
  }
}

float &Vector3D::operator[](const int index) {
  switch (index) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  default:
    throw std::out_of_range("Vector3D index range is 0-2");
  }
}

const Vector3D &Vector3D::operator=(const Vector3D &rhs)
{
  x = rhs.x;
  y = rhs.y;
  z = rhs.z;
  return *this;
}

const Vector3D &Vector3D::operator+=(const Vector3D &rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

const Vector3D &Vector3D::operator-=(const Vector3D &rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  return *this;
}

const Vector3D &Vector3D::operator*=(const Vector3D &rhs)
{
  x *= rhs.x;
  y *= rhs.y;
  z *= rhs.z;
  return *this;
}

const Vector3D &Vector3D::operator/=(const Vector3D &rhs)
{
  x /= rhs.x;
  y /= rhs.y;
  z /= rhs.z;
  return *this;
}

const Vector3D &Vector3D::operator*=(const float &rhs)
{
  x *= rhs;
  y *= rhs;
  z *= rhs;
  return *this;
}

float Vector3D::length() const
{
  return sqrt(x * x + y * y + z * z);
}

const float Vector3D::dotProduct(const Vector3D &rhs) const
{
  return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3D Vector3D::unitVector() const
{
  float length = this->length();

  return Vector3D(x / length, y / length, z / length);
}

const Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs)
{
  return Vector3D(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

const Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs)
{
  return Vector3D(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

const Vector3D operator*(const float lhs, const Vector3D &rhs)
{
  return rhs.scale(lhs);
}

const Vector3D operator*(const Vector3D &lhs, const float rhs)
{
  return lhs.scale(rhs);
}

const Vector3D operator*(const Vector3D &lhs, const Vector3D &rhs)
{
  return Vector3D(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}

const Vector3D operator/(const Vector3D &lhs, const Vector3D &rhs)
{
  return Vector3D(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
}

bool operator==(const Vector3D &lhs, const Vector3D &rhs)
{
  return (lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2]);
}

}// namespace utils