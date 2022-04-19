#include "BlinnPhongMirroredShader.h"

namespace renderer {

BlinnPhongMirroredShader::BlinnPhongMirroredShader()
  : bp(), mirror(), mirrorCoefficient(0.5f) {}

BlinnPhongMirroredShader::BlinnPhongMirroredShader(Vector3D d, Vector3D s, float e, float mCoef)
  : bp(d, s, e), mirror(), mirrorCoefficient(mCoef) {}

Vector3D renderer::BlinnPhongMirroredShader::apply(const HitStructure &h, SceneContainer &sc, int depth) const
{
  return (mirrorCoefficient * mirror.apply(h, sc, depth)) + ((1 - mirrorCoefficient) * bp.apply(h, sc, depth));
}

}// namespace renderer