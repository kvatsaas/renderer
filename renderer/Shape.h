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

  virtual std::string getName() = 0;
  
  virtual bool closestHit(const Ray &r) = 0; //will need to add other parameters; return true if ray intersects shape
};
}// namespace renderer