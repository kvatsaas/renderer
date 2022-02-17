#pragma once
#include "Shape.h"
#include "Ray.h"

namespace renderer {

class Sphere : public Shape
{
public:
  /**
   * @brief Creates a default sphere
   */
  Sphere();

  Sphere(Vector3D c, float r, Shader *s, Vector3D col = Vector3D(1, 1, 1));

  /**
   * @brief Determines whether the given ray intersects with this triangle
   * @param r The Ray object
   * @return True if it intersects, otherwise false
  */
  bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit);

  /**
   * @brief For now, returns the "average" color of all three vertices.
   * @return The color of the triangle
  */
  Vector3D getColor();

protected:
  Vector3D center, color;
  float radius;
};
}// namespace renderer