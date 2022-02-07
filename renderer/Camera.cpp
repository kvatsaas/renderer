#include "Camera.h"

namespace renderer {



std::string Camera::getName()
{
  return name;
}

Vector3D &Camera::getPosition()
{
  return position;
}

CoordSys &Camera::getCoord()
{
  return coord;
}

}// namespace renderer