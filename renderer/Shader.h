#pragma once
#include <string>
#include <vector>
#include "HitStructure.h"
#include "Light.h"

namespace renderer {

class SceneContainer;// forward declaration

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
   *        For the basic shader, the value is constant and the parameters are ignored.
   * @param h The hit structure
   * @param sc The scene container
   * @param depth The current recursive depth of the ray
   * @return The ambient color of this basic shader
  */
  virtual Vector3D apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const;

  /**
   * @brief Getter for the name
   * @return The name of the shader
  */
  std::string getName() const;

  /**
   * @brief Setter for the name
   * @param n The name of the shader
  */
  void setName(std::string n);

protected:
  std::string name;
  Vector3D ambient;
};
}// namespace renderer