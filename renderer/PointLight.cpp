#include "PointLight.h"
#include "SceneContainer.h"

namespace renderer {

PointLight::PointLight()
{
  position = Vector3D(0.0, 0.0, 0.0);
  intensity = Vector3D(1.0, 1.0, 1.0);
}

PointLight::PointLight(Vector3D p, Vector3D i)
{
  position = p;
  intensity = i;
}

boost::optional<Vector3D> PointLight::isVisibleFrom(Vector3D point, int depth, SceneContainer &sc, boost::optional<std::vector<std::pair<float, float>>> jitter, int r)
{
  auto lightRayDir = position - point;// direction from point to light
  boost::optional<Vector3D> out;
  if (!sc.anyHit(Ray(point, lightRayDir), 0.0001f, 1.0f, depth)) {
    out = position;
  }
  return out;
}

}// namespace renderer