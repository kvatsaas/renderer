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
  
  auto directions = std::vector<Vector3D>();
  auto intensities = std::vector<Vector3D>();
  sc.gatherLightSamples(normal.getOrigin(), depth, directions, intensities);

  auto n = normal.getDirection();
  auto v = -1.0 * h.getHit().getDirection().normalize();
  for (int i = 0; i < directions.size(); i++) {
    auto l = directions[i];// light direction
    auto lambert = n.dotProduct(l);
    if (lambert > 0)
      diffColor += (diffuse * intensities[i]) * lambert;

    auto n_dot_h = n.dotProduct((l + v).normalize());
    if (n_dot_h > 0)
      specColor += (specular * intensities[i]) * pow(n_dot_h, exp);
  }

  return diffColor + specColor;
}

}// namespace renderer
