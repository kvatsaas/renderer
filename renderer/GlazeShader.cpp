#include "GlazeShader.h"

namespace renderer {

renderer::GlazeShader::GlazeShader()
  : lambert(), mirror(), mirrorCoefficient(0.5f) {}

renderer::GlazeShader::GlazeShader(Vector3D d, float mCoef)
  : lambert(d), mirror(), mirrorCoefficient(mCoef) {}

Vector3D renderer::GlazeShader::apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const
{
  return (mirrorCoefficient * mirror.apply(h, sc, depth, jitter, r)) + ((1 - mirrorCoefficient) * lambert.apply(h, sc, depth, jitter, r));
}

}// namespace renderer