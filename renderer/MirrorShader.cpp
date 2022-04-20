#include <limits>
#include "MirrorShader.h"


namespace renderer {
Vector3D MirrorShader::apply(const HitStructure &h, SceneContainer &sc, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const
{
  auto v = -1.0 * h.getHit().getDirection().normalize();
  auto n = h.getNormal().getDirection();
  auto ray = Ray(h.getNormal().getOrigin(), (-1.0 * v) + 2 * (n.dotProduct(v) * n));
  return sc.rayColor(ray, 0.0001f, std::numeric_limits<float>::max(), depth + 1);
}
}// namespace renderer