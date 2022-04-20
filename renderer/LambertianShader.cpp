#include "LambertianShader.h"

namespace renderer {
LambertianShader::LambertianShader()
  : diffuse(1, 1, 1) {}

LambertianShader::LambertianShader(Vector3D d)
  : diffuse(d) {}

Vector3D LambertianShader::apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const
{
  auto diffColor = Vector3D();
  auto normal = h.getNormal();
  auto visibleLights = sc.getVisibleLights(normal.getOrigin(), depth, jitter, r);

  auto n = normal.getDirection();
  for (int i = 0; i < visibleLights.size(); i++) {
    auto l = (visibleLights[i]->getPosition(jitter, r) - normal.getOrigin()).normalize();// light direction
    auto lambert = n.dotProduct(l);
    if (lambert > 0)
      diffColor += (diffuse * visibleLights[i]->getIntensity()) * lambert;
  }

  return diffColor;
}
}// namespace renderer
