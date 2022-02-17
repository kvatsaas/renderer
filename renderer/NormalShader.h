#pragma once
#include "Shader.h"

namespace renderer {

class NormalShader : public Shader
{
public:
  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @return The normal in the hit structure, mapped to the [0,1] space as a color
  */
  virtual Vector3D apply(const HitStructure &h) const;
};
}// namespace renderer