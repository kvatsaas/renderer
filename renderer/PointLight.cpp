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

void PointLight::getLightSamples(Vector3D point, int depth, SceneContainer &sc, std::vector<Vector3D> &directions, std::vector<Vector3D> &intensities)
{
  auto lightRayDir = position - point;// direction from point to light
  if (!sc.anyHit(Ray(point, lightRayDir), 0.0001f, 1.0f, depth)) {
    directions.push_back(lightRayDir.normalize());// must normalize before sending to shader
    intensities.push_back(intensity);
  }
}

}// namespace renderer