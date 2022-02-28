#pragma once
#include "Vector3D.h"
#include "Ray.h"

namespace renderer {

class Shader; // forward declaration
class Shape; //forward declaration

class HitStructure
{
public:
  /**
   * @brief Creates an empty hit structure with null or default values.
  */
  HitStructure();

  /**
   * @brief Creates a hit structure with the given values.
   * @param s A pointer to the shader
   * @param s A pointer to the shape
   * @param h The ray that performed the hit
   * @param n The normal at the hit point
   * @param t The t-value for the hit
  */
  HitStructure(Shader *s, Shape *sp, Ray h, Ray n, float t);

  /**
   * @brief Getter for the shader
   * @return The shader
  */
  const Shader *getShader() const;

  /**
   * @brief Getter for the shape
   * @return The shape
  */
  const Shape *getShape() const;

  /**
   * @brief Getter for the ray that hit the shape
   * @return The ray that hit the shape
  */
  const Ray &getHit() const;

  /**
   * @brief Getter for the normal
   * @return The normal
  */
  const Ray &getNormal() const;

  /**
   * @brief Getter for the t-value for the intersection
   * @return The t-value for the intersection
  */
  float get_t() const;

protected:
  Shader *shaderPtr;
  Shape *shapePtr;
  Ray hit; // ray that hit
  Ray normal;
  float t; // t value at collision point
};

}// namespace renderer