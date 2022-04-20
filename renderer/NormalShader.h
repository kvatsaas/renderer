#pragma once
#include "Shader.h"
#include "Shape.h"
#include "SceneContainer.h"

namespace renderer {

class NormalShader : public Shader
{
public:
  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color mapping for the normal at the hit point
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const;
};
}// namespace renderer