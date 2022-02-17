#pragma once
#include <string>
#include "Vector3D.h"
#include "HitStructure.h"

namespace renderer {

class Shader
{
public:
  Shader();
  Shader(const Vector3D amb);

  virtual Vector3D apply(const HitStructure &h) const;

  std::string getName() const;

protected:
  std::string name;
  Vector3D ambient;
};
}// namespace renderer