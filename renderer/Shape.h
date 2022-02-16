#pragma once
#include <vector>
#include <string>
#include "Vector3D.h"
#include "Ray.h"
#include "Shader.h"
#include "HitStructure.h"

namespace renderer {

class Shape
{
public:
  Shape();
  ~Shape(){};

  /**
   * @brief Determines whether the given ray intersects with this shape
   * @param r The Ray object
   * @return True if it intersects, otherwise false
  */
  virtual bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit) = 0;

protected:
  Shader *shaderPtr;

};
}// namespace renderer