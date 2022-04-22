#include "AreaLight.h"
#include <ctime>

#include "SceneContainer.h"

namespace renderer {

AreaLight::AreaLight()
  : normal(0, -1, 0), width(1), length(1)
{
  intensity = Vector3D(1, 1, 1);

  normal.normalize();
  coord = CoordSys(normal);

  // position is the lower left corner of the light, i.e. min point
  position = Vector3D() - (coord.get_u() * width / 2) - (coord.get_v() * length / 2);
}

AreaLight::AreaLight(Vector3D p, Vector3D i, Vector3D nv, float w, float l, int nr)
  : normal(nv), width(w), length(l), n(nr)
{
  intensity = i;

  normal.normalize();
  coord = CoordSys(normal);

  // position is the lower left corner of the light, i.e. min point
  position = p - (coord.get_u() * width / 2) - (coord.get_v() * length / 2);
}

const Vector3D AreaLight::getPosition(boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const
{
  if (jitter.has_value()) {
    int i = r / n;
    int j = r % n;
    float u_offset = (i + jitter.get()[r].first) / n * width;
    float v_offset = (j + jitter.get()[r].second) / n * length;

    auto jitterPos = position + (coord.get_u() * u_offset) + (coord.get_v() * v_offset);
    return jitterPos;

  } else {// no AA - just use center of area light
    auto lightPos = position + (coord.get_u() * width / 2.0) + (coord.get_v() * length / 2.0);
    return lightPos;
  }
}

CoordSys AreaLight::getCoord()
{
  return coord;
}

boost::optional<Vector3D> AreaLight::isVisibleFrom(Vector3D point, int depth, SceneContainer &sc, boost::optional<std::vector<std::pair<float, float>>> jitter, int r)
{
  boost::optional<Vector3D> out;
  auto position = getPosition(jitter, r);
  auto lightRayDir = position - point;// direction from point to jittered light position
  if (!sc.anyHit(Ray(point, lightRayDir), 0.0001f, 1.0f, depth)) {
    out = position;
  }
  return out;
}

}// namespace renderer