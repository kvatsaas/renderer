#include "NormalShader.h"
#include <ctime>

namespace renderer {

Vector3D NormalShader::apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const
{
  return h.getNormal().directionToColor();
}

}// namespace renderer