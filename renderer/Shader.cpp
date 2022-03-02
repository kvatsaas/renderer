#include <ctime>
#include "Shader.h"
#include "SceneContainer.h"

namespace renderer {

Shader::Shader()
{
  srand(static_cast<unsigned>(time(0)));
  float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

  ambient = Vector3D(x, y, z);
}

Shader::Shader(const Vector3D amb)
  : ambient(amb) {}

Vector3D Shader::apply(const HitStructure &h, SceneContainer &sc, int depth) const
{
  return ambient;
}

std::string Shader::getName() const
{
  return name;
}
void Shader::setName(std::string n)
{
  name = n;
}
}// namespace renderer