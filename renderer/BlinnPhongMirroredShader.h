#pragma once
#include "Shader.h"
#include "BlinnPhongShader.h"
#include "MirrorShader.h"

namespace renderer {

class BlinnPhongMirroredShader : public Shader
{
public:
  /**
   * @brief Creates a mirrored BP shader with a default BP shader and mirror coefficient of 0.5
  */
  BlinnPhongMirroredShader();

  /**
   * @brief Creates a mirrored BP shader using the given BP shader values and mirror coefficient.
   * @param d The diffuse value
   * @param s The specular value
   * @param e The Phong exponent
   * @param mCoef The mirror coefficient
  */
  BlinnPhongMirroredShader(Vector3D d, Vector3D s, float e, float mCoef);

  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color for the hit structure
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth) const;

private:
  BlinnPhongShader bp;
  MirrorShader mirror;
  float mirrorCoefficient;
};

}// namespace renderer
