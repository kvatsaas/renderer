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
   * @return The normal in the hit structure, mapped to the [0,1] space as a color
  */
  class SceneContainer;// forward declaration

  /**
   * @brief Returns the color for the given hit structure.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The color mapping for the normal at the hit point
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth) const;
};
}// namespace renderer