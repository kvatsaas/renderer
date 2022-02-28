#include "NormalShader.h"
#include <ctime>

namespace renderer {

Vector3D NormalShader::apply(const HitStructure &h, SceneContainer &sc) const
{
  return h.getNormal().directionToColor();
}

}// namespace renderer