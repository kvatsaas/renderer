#pragma once

#include <memory>
#include "Shape.h"
#include <glm/ext/matrix_float4x4.hpp>

namespace renderer {

class InstancedObject : public Shape
{
public:
  InstancedObject(Shape *&refShape, glm::mat4 &m, glm::mat4 &mInv);

  /**
   * @brief Determines whether the given ray intersects with the box at this node and modifies
   *        the given hit structure if it does
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @param hit A HitStructure that will be filled in the event of a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth);

  /**
   * @brief Determines whether the given ray intersects with this node
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool hit(const Ray &r, float tmin, float tmax, int depth);

private:
  Shape *refShape;
  glm::mat4 mInv, mTransposeInv;
};

}// namespace renderer
