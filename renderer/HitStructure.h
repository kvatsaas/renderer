#pragma once
#include "Vector3D.h"
#include "Ray.h"

namespace renderer {

class Shader; // forward declaration

class HitStructure
{
public:
  /**
   * @brief Creates an empty hit structure with null or default values.
  */
  HitStructure();

  /**
   * @brief Creates a hit structure with the given values.
   * @param s A pointer to a shader
   * @param c A color
   * @param h The ray that performed the hit
   * @param n The normal at the hit point
   * @param t The t-value for the hit
  */
  HitStructure(Shader *s, Vector3D c, Ray h, Ray n, float t);

  const Shader *getShader() const;
  const Vector3D &getColor() const;
  const Ray &getHit() const;
  const Ray &getNormal() const;
  float get_t() const;

protected:
  Shader *shaderPtr;
  Vector3D color;// use in place of shader for now
  Ray hit;// ray that hit
  Ray normal;
  float t;// t value at collision point
};

}// namespace renderer