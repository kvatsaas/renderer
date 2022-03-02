#pragma once
#include "Shader.h"
#include "SceneContainer.h"

namespace renderer {

class MirrorShader : public Shader
{
public:
  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color for the hit structure
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth) const;
};

}// namespace renderer