#include "LambertianShader.h"

namespace renderer {
LambertianShader::LambertianShader()
  : diffuse(1, 1, 1) {}

LambertianShader::LambertianShader(Vector3D d)
  : diffuse(d) {}

Vector3D LambertianShader::apply(const HitStructure &h, SceneContainer &sc, int depth) const
{
  auto diffColor = Vector3D();
  auto normal = h.getNormal();

  auto directions = std::vector<Vector3D>();
  auto intensities = std::vector<Vector3D>();
  sc.gatherLightSamples(normal.getOrigin(), depth, directions, intensities);

  auto n = normal.getDirection();
  for (int i = 0; i < directions.size(); i++) {
    auto l = directions[i];// light direction
    auto lambert = n.dotProduct(l);
    if (lambert > 0)
      diffColor += (diffuse * intensities[i]) * lambert;
  }

  return diffColor;
}
}// namespace renderer
