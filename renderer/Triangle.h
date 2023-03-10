#pragma once
#include "Shape.h"
#include "Ray.h"
#include "Framebuffer.h"

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
   * @param vertex_a The location of vertice a
   * @param vertex_b The location of vertice b
   * @param vertex_c The location of vertice c
   * @param s A shader for the triangle
  */
  Triangle(Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c, Shader *s = nullptr);

  /**
   * @brief Creates a triangle with the given vertices and a solid color
   * @param vertex_a The location of vertice a
   * @param vertex_b The location of vertice b
   * @param vertex_c The location of vertice c
   * @param col The color of the triangle
   * @param s A shader for the triangle
  */
  Triangle(Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c, Vector3D col, Shader *s = nullptr);

  /**
   * @brief Creates a triangle with the given vertices and colors
   * @param vertex_a The location of vertice a
   * @param vertex_b The location of vertice b
   * @param vertex_c The location of vertice c
   * @param a_col The color of vertice a
   * @param b_col The color of vertice b
   * @param c_col The color of vertice c
   * @param s A shader for the triangle
  */
  Triangle(Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c, Vector3D a_rgb, Vector3D b_rgb, Vector3D c_rgb, Shader *s = nullptr);

  /**
   * @brief Setter for the normal values
   * @param normal_a The normal at a
   * @param normal_b The normal at b
   * @param normal_c The normal at c
   * @param interp Set this to false if you don't want the shading to interpolate normals. Defaults to true
  */
  void setNormals(Vector3D normal_a, Vector3D normal_b, Vector3D normal_c, bool interp = true);

  /**
   * @brief Determines whether the given ray intersects with this triangle and modifies the given hit
   *        structure if it does
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @param hit A HitStructure that will be filled in the event of a hit
   * @return True if it intersects, otherwise false
  */
  bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth);

  /**
   * @brief Determines whether the given ray intersects with this triangle
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool hit(const Ray &r, float tmin, float tmax, int depth);

  /**
   * @brief Rasterizes a triangle in a 2D scene on the given framebuffer
   * @param fb The framebuffer to use
  */
  void rasterize2D(Framebuffer &fb);

  /**
   * @brief Returns the direction of the normal to the plane of the triangle. Note that the inverted
   *        value is also normal to the plane.
   * @return The normal direction
  */
  const Vector3D &getNormalDirection();

protected:
  Vector3D a, b, c, a_norm, b_norm, c_norm, a_col, b_col, c_col;
  Vector3D normalDirection;
  bool interpolateNormals = false;

  /**
   * @brief Calculates the bounding box and assigns it to bound
  */
  void calculateBoundingBox();

  /**
   * @brief Calculates the centroid and assigns it to center
  */
  void calculateCentroid();

  void calculateBarycentricCoordinates(float x, float y, float &alpha, float &beta, float &gamma);
};

float implicitLine(float x, float y, Vector3D v0, Vector3D v1);
}// namespace renderer