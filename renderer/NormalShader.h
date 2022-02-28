#pragma once
#include "Shader.h"
#include "Shape.h"

namespace renderer {

class NormalShader : public Shader
{
public:
  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @return The normal in the hit structure, mapped to the [0,1] space as a color
  */
  class SceneContainer;// forward declaration
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc) const;
};
}// namespace renderer