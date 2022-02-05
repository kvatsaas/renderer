#pragma once
#include "Vector3D.h"

namespace renderer {

class Ray
{
public:
  Ray(Vector3D &o, Vector3D &d)
    : origin(o), direction(d) {}

  Vector3D &getOrigin();
  Vector3D &getDirection();

  void setOrigin(Vector3D &o);
  void setDirection(Vector3D &d);

protected:
  Vector3D origin, direction;
};

};