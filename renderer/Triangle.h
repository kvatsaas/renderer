#pragma once
#include "Shape.h"
#include "Ray.h"

namespace renderer {

class Triangle : public Shape
{
public:
  /**
   * @brief Creates a white equilateral triangle centered on (0,0,0) and facing the z axis
  */
  Triangle();

  /**
   * @brief Creates a white triangle with the given vertices
   * @param a The location of vertice a
   * @param b The location of vertice b
   * @param c The location of vertice c
  */
  Triangle(Vector3D a, Vector3D b, Vector3D c);

  /**
   * @brief Creates a triangle with the given vertices and a solid color
   * @param a The location of vertice a
   * @param b The location of vertice b
   * @param c The location of vertice c
   * @param col The color of the triangle
  */
  Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D col);

  /**
   * @brief Creates a triangle with the given vertices and colors
   * @param a The location of vertice a
   * @param b The location of vertice b
   * @param c The location of vertice c
   * @param a_col The color of vertice a
   * @param b_col The color of vertice b
   * @param c_col The color of vertice c
  */
  Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D a_col, Vector3D b_col, Vector3D c_col);

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
  Vector3D v_a, v_b, v_c, a_rgb, b_rgb, c_rgb, color;
};
}// namespace renderer