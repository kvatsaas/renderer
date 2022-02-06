#pragma once
#include <vector>
#include <string>
#include "Vector3D.h"
#include "Ray.h"

namespace renderer {

class Shape
{
public:
  virtual ~Shape() = 0;
  
  /**
   * @brief Determines whether the given ray intersects with this shape
   * @param r The Ray object
   * @return True if it intersects, otherwise false
  */
  virtual bool closestHit(const Ray &r, const float focalLength) = 0;
};
}// namespace renderer