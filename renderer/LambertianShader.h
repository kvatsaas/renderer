#pragma once
#include "Shader.h"
#include "SceneContainer.h"

namespace renderer {

class LambertianShader : public Shader
{
public:
  /**
   * @brief Creates a Lambertian shader with a diffuse value of (1, 1, 1);
  */
  LambertianShader();

  /**
   * @brief Creates a Lambertian shader with the given diffuse value.
   * @param diffuse 
  */
  LambertianShader(Vector3D diffuse);

  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color for the hit structure
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth) const;

private:
  Vector3D diffuse;
};

}// namespace renderer