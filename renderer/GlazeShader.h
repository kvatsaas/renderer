#pragma once
#include "Shader.h"
#include "LambertianShader.h"
#include "MirrorShader.h"

namespace renderer {

class GlazeShader : public Shader
{
public:
  /**
   * @brief Creates a Glaze shader with a diffuse value of (1, 1, 1) and mirror coefficient of 0.5
  */
  GlazeShader();

  /**
   * @brief Creates a Lambertian shader with the given diffuse value.
   * @param diffuse 
  */
  GlazeShader(Vector3D d, float mCoef);

  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color for the hit structure
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth) const;

private:
  LambertianShader lambert;
  MirrorShader mirror;
  float mirrorCoefficient;
};

}// namespace renderer
