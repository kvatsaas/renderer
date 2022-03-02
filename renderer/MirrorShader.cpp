#include <limits>
#include "MirrorShader.h"


namespace renderer {
Vector3D MirrorShader::apply(const HitStructure &h, SceneContainer &sc, int depth) const
{
  auto v = -1.0 * h.getHit().getDirection().normalize();
  auto n = h.getNormal().getDirection();
  auto r = Ray(h.getNormal().getOrigin(), (-1.0 * v) + 2 * (n.dotProduct(v) * n));
  return sc.rayColor(r, 0.0001f, std::numeric_limits<float>::max(), depth);
}
}// namespace renderer