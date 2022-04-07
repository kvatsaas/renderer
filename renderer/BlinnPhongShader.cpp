#include <cmath>
#include "BlinnPhongShader.h"

namespace renderer {
BlinnPhongShader::BlinnPhongShader()
  : diffuse(1, 1, 1), specular(1, 1, 1), exp(1.0) {}

BlinnPhongShader::BlinnPhongShader(Vector3D d, Vector3D s, float e)
  : diffuse(d), specular(s), exp(e) {}

Vector3D BlinnPhongShader::apply(const HitStructure &h, SceneContainer &sc, int depth) const
{
  auto diffColor = Vector3D();
  auto specColor = Vector3D();
  auto normal = h.getNormal();
  auto visibleLights = sc.getVisibleLights(normal.getOrigin(), depth);

  auto n = normal.getDirection();
  auto v = -1.0 * h.getHit().getDirection().normalize();
  for (int i = 0; i < visibleLights.size(); i++) {
    auto l = (visibleLights[i]->getPosition() - normal.getOrigin()).normalize();// light direction
    auto lambert = n.dotProduct(l);
    if (lambert > 0)
      diffColor += (diffuse * visibleLights[i]->getIntensity()) * lambert;

    auto n_dot_h = n.dotProduct((l + v).normalize());
    if (n_dot_h > 0)
      specColor += (specular * visibleLights[i]->getIntensity()) * pow(n_dot_h, exp);
  }

  return diffColor + specColor;
}

}// namespace renderer
