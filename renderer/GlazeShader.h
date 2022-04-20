#pragma once
#include "Shader.h"
#include "LambertianShader.h"
#include "MirrorShader.h"

namespace renderer {

class GlazeShader : public Shader
{
public:
  /**
   * @brief Creates a Glaze shader with a default Lambertian shader and mirror coefficient of 0.5
  */
  GlazeShader();

  /**
   * @brief Creates a Glaze shader using the given diffuse value and mirror coefficient.
   * @param d The diffuse value
   * @param mCoef The mirror coefficient
  */
  GlazeShader(Vector3D d, float mCoef);

  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color for the hit structure
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const;

private:
  LambertianShader lambert;
  MirrorShader mirror;
  float mirrorCoefficient;
};

}// namespace renderer
