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

bool PointLight::isVisibleFrom(Vector3D point, int depth, SceneContainer &sc)
{
  auto lightRayDir = (position - point);// direction from point to light
  return !sc.anyHit(Ray(point, lightRayDir), 0.0001f, 1.0f, depth);
}

}// namespace renderer