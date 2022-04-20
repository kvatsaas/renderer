#include "Ray.h"

namespace renderer {
const Vector3D &Ray::getOrigin() const
{
  return origin;
}

const Vector3D &Ray::getDirection() const
{
  return direction;
}
const int &Ray::getJitterIndex() const
{
  return jitterIndex;
}
void Ray::setOrigin(Vector3D &o)
{
  origin = o;
}
void Ray::setDirection(Vector3D &d)
{
  direction = d;
}

void Ray::setJitterIndex(int ji)
{
  jitterIndex = ji;
}

Vector3D Ray::directionToColor() const
{
  return (direction.normalize() + Vector3D(1, 1, 1)) * 0.5;
}
}// namespace renderer