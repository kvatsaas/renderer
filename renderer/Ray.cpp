#include "Ray.h"

namespace renderer {
Vector3D &Ray::getOrigin()
{
  return origin;
}

Vector3D &Ray::getDirection()
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
}// namespace renderer