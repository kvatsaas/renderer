#pragma once
#include "Shader.h"
#include "SceneContainer.h"

namespace renderer {

class BlinnPhongShader : public Shader
{
public:
  /**
   * @brief Creates a Blinn-Phong shader with diffuse and specular values of (1, 1, 1)
   *        and an exponent of 1.0
  */
  BlinnPhongShader();

  /**
   * @brief Creates a Blinn-Phong shader with the given values
   * @param d The diffuse value
   * @param s The specular value
   * @param e The Phong exponent
  */
  BlinnPhongShader(Vector3D d, Vector3D s, float e);

  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color for the hit structure
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const;

protected:
  Vector3D diffuse, specular;
  float exp;
};

}// namespace renderer