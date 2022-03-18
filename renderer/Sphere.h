#pragma once
#include "Shape.h"
#include "Ray.h"

namespace renderer {

class Sphere : public Shape
{
public:
  /**
   * @brief Creates a white sphere at (0, 0, 0) with a radius of 1
   */
  Sphere();

  /**
   * @brief Creates a sphere with the given attributes
   * @param c The center of the sphere
   * @param r The radius of the sphere
   * @param s A shader for the sphere
   * @param col The color of the sphere. Defaults to white
  */
  Sphere(Vector3D c, float r, Shader *s = nullptr, Vector3D col = Vector3D(1, 1, 1));

  /**
   * @brief Determines whether the given ray intersects with this sphere and modifies the given hit
   *        structure if it does
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @param hit A HitStructure that will be filled in the event of a hit
   * @return True if it intersects, otherwise false
  */
  bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit);

   /**
   * @brief Determines whether the given ray intersects with this sphere
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool hit(const Ray &r, float tmin, float tmax);

  /**
   * @brief Returns the color of the sphere
   * @return The color of the sphere
  */
  Vector3D getColor();

protected:
  Vector3D color;
  float radius;
};
}// namespace renderer