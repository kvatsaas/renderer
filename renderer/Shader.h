#pragma once
#include <string>
#include "Vector3D.h"
#include "HitStructure.h"

namespace renderer {

class Shader
{
public:
  /**
   * @brief Creates a basic shader with a random ambient color
  */
  Shader();

  /**
   * @brief Creates a basic shader with the given ambient color
   * @param amb The ambient color
  */
  Shader(const Vector3D amb);

  /**
   * @brief Returns the color for the given hit structure.
   *        For the basic shader, the value is constant and the hit structure is ignored.
   * @param h The hit structure
   * @return The ambient color of this basic shader
  */
  virtual Vector3D apply(const HitStructure &h) const;

  std::string getName() const;

protected:
  std::string name;
  Vector3D ambient;
};
}// namespace renderer