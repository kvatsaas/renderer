#include "LambertianShader.h"

namespace renderer {
LambertianShader::LambertianShader()
  : diffuse(1, 1, 1) {}

LambertianShader::LambertianShader(Vector3D d)
  : diffuse(d) {}

Vector3D LambertianShader::apply(const HitStructure &h, SceneContainer &sc) const
{
  auto diffColor = Vector3D();
  auto normal = h.getNormal();
  auto visibleLights = sc.getVisibleLights(normal.getOrigin(), h.getShape());

  auto n = normal.getDirection();
  for (int i = 0; i < visibleLights.size(); i++) {
    auto l = (visibleLights[i]->getPosition() - normal.getOrigin()).normalize();// light direction
    auto lambert = n.dotProduct(l);
    if (lambert > 0)
      diffColor += (diffuse * visibleLights[i]->getIntensity()) * lambert;
  }

  diffColor.bound(diffuse);
  return diffColor;
}
}// namespace renderer
