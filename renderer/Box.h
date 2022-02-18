#pragma once
#include "Shape.h"
#include "Triangle.h"

namespace renderer {

class Box : public Shape
{
public:
  /**
   * @brief Creates a box from (0,0,0) to (1,1,1) with a null shader.
  */
  Box();

  /**
   * @brief Creates a box with the given attributes
   * @param minPoint The minimum point of the cube (opposite maxPoint)
   * @param maxPoint The maximum point of the cube (opposite minPoint)
   * @param s 
  */
  Box(Vector3D minPoint, Vector3D maxPoint, Shader *s = nullptr);

  /**
   * @brief Determines whether the given ray intersects with this box
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @param hit A HitStructure that will be filled in the event of a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit);

  /**
   * @brief Getter for the shader
   * @return The shader
  */
  virtual void setShader(Shader *s);

protected:
  std::vector<Triangle> triangles;
};
}// namespace renderer