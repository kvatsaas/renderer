#pragma once
#include "Shape.h"
#include "Ray.h"

namespace renderer {

class Triangle : Shape
{
public:
  /**
   * @brief Creates an equilateral triangle centered on (0,0,0) and facing the z axis
  */
  Triangle();

  /**
   * @brief Creates a triangle with the given attributes
   * @param a_vert The location of vertice a
   * @param b_vert The location of vertice b
   * @param c_vert The location of vertice c
   * @param a_col The color of vertice a
   * @param b_col The color of vertice b
   * @param c_col The color of vertice c
  */
  Triangle(Vector3D a_vert, Vector3D b_vert, Vector3D c_vert, Vector3D a_col, Vector3D b_col, Vector3D c_col);

  /**
   * @brief Determines whether the given ray intersects with this triangle within the image
   * @param r The Ray object
   * @return True if it intersects, otherwise false
  */
  bool closestHit(const Ray &r);

protected:
  Vector3D a, b, c, a_rgb, b_rgb, c_rgb;
};
}// namespace renderer