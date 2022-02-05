#pragma once
#include "Shape.h"
#include "Ray.h"

namespace renderer {

class Triangle : Shape
{
public:
  Triangle();
  Triangle(Vector3D a_vert, Vector3D b_vert, Vector3D c_vert, Vector3D a_col, Vector3D b_col, Vector3D c_col);

  bool closestHit(const Ray &r);

protected:
  Vector3D a, b, c, a_rgb, b_rgb, c_rgb;
};
}// namespace renderer