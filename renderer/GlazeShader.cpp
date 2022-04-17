#include "GlazeShader.h"

namespace renderer {

renderer::GlazeShader::GlazeShader() : lambert(Vector3D(1, 1, 1)), mirror(), mirrorCoefficient(0.5f) {}

renderer::GlazeShader::GlazeShader(Vector3D d, float mCoef) : lambert(d), mirror(), mirrorCoefficient(mCoef) {}

Vector3D renderer::GlazeShader::apply(const HitStructure &h, SceneContainer &sc, int depth) const
{
  return (mirrorCoefficient * mirror.apply(h, sc, depth)) + ((1 - mirrorCoefficient) * lambert.apply(h, sc, depth));
}

}// namespace renderer