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
void Ray::setOrigin(Vector3D &o)
{
  origin = o;
}
void Ray::setDirection(Vector3D &d)
{
  direction = d;
}
Vector3D Ray::directionToColor()
{
  return (direction.unitVector() + Vector3D(1, 1, 1)) * 0.5;
}
}// namespace renderer