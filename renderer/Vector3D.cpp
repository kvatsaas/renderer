#include "Vector3D.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace renderer {

Vector3D::Vector3D()
  : x(0), y(x), z(x) {}

Vector3D::Vector3D(float a, float b, float c)
  : x(a), y(b), z(c) {}

Vector3D::Vector3D(const Vector3D &v)
  : x(v.x), y(v.y), z(v.z) {}

Vector3D::Vector3D(const std::string str)
{
  std::vector<std::string> args;
  boost::split(args, str, boost::is_any_of(" "));
  x = std::stof(args[0]);
  y = std::stof(args[1]);
  z = std::stof(args[2]);
}

Vector3D Vector3D::scale(const float scalar) const
{
  return Vector3D(x * scalar, y * scalar, z * scalar);
}

void Vector3D::bound(const float min, const float max)
{
  if (x < min)
    x = min;
  else if (x > max)
    x = max;

  if (y < min)
    y = min;
  else if (y > max)
    y = max;

  if (z < min)
    z = min;
  else if (z > max)
    z = max;
}

const float Vector3D::operator[](const int index) const
{
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

float &Vector3D::operator[](const int index)
{
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

const float Vector3D::operator[](const char index) const
{
  switch (index) {
  case 'x':
    return x;
  case 'y':
    return y;
  case 'z':
    return z;
  default:
    throw std::out_of_range("Vector3D index range is 0-2");
  }
}

float &Vector3D::operator[](const char index)
{
  switch (index) {
  case 'x':
    return x;
  case 'y':
    return y;
  case 'z':
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

Vector3D &Vector3D::operator=(const std::string str)
{
  std::vector<std::string> args;
  boost::split(args, str, boost::is_any_of(" "));
  x = std::stof(args[0]);
  y = std::stof(args[1]);
  z = std::stof(args[2]);
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

const Vector3D Vector3D::crossProduct(const Vector3D &rhs) const
{
  float i, j, k;
  i = (this->y * rhs.z) - (this->z * rhs.y);
  j = -((this->x * rhs.z) - (this->z * rhs.x));
  k = (this->x * rhs.y) - (this->y * rhs.x);
  return Vector3D(i, j, k);
}

Vector3D Vector3D::normalize() const
{
  float length = this->length();

  return Vector3D(x / length, y / length, z / length);
}

std::string Vector3D::toString() const
{
  return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
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

const Vector3D operator/(const Vector3D &lhs, const float rhs)
{
  return lhs.scale(1.0 / rhs);
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
