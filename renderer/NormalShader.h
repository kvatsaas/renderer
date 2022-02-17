#pragma once
#include "Shader.h"

namespace renderer {

class NormalShader : public Shader
{
public:
  virtual Vector3D apply(const HitStructure &h) const;
};
}// namespace renderer