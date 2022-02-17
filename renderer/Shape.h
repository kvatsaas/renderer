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

  /**
   * @brief Determines whether the given ray intersects with this shape
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @param hit A HitStructure that will be filled in the event of a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit) = 0;

  /**
   * @brief Getter for the shader
   * @return The shader
  */
  void setShader(Shader *s);

  /**
   * @brief Getter for the shader
   * @return The shader
  */
  const Shader *getShader() const;

protected:
  Shader *shaderPtr;
};
}// namespace renderer