#include "AreaLight.h"
#include <ctime>

#include "SceneContainer.h"

namespace renderer {

AreaLight::AreaLight()
  : normal(0, -1, 0), width(1), length(1)
{
  intensity = Vector3D(1, 1, 1);
  subIntensity = intensity;

  normal.normalize();
  coord = CoordSys(normal);

  // position is the lower left corner of the light, i.e. min point
  position = Vector3D() - (coord.get_u() * width / 2) - (coord.get_v() * length / 2);
}

AreaLight::AreaLight(Vector3D p, Vector3D i, Vector3D nv, float w, float l, int nr)
  : normal(nv), width(w), length(l), n(nr)
{
  intensity = i;
  if (n > 1)
    subIntensity = intensity / (n * n);
  else
    subIntensity = intensity;

  normal.normalize();
  coord = CoordSys(normal);

  // position is the lower left corner of the light, i.e. min point
  position = p - (coord.get_u() * width / 2) - (coord.get_v() * length / 2);
}

CoordSys AreaLight::getCoord()
{
  return coord;
}

void AreaLight::getLightSamples(Vector3D point, int depth, SceneContainer &sc, std::vector<Vector3D> &directions, std::vector<Vector3D> &intensities)
{
  if (n > 1) {
    auto rays = std::vector<Ray>();
    float p_xi, q_xi;
    Vector3D jitterPos, partial, lightRayDir;
    srand(static_cast<unsigned>(time(0)));

    for (int p = 0; p < n; p++) {
      for (int q = 0; q < n; q++) {
        p_xi = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        q_xi = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        partial = position + (coord.get_u() * width / p_xi);// save calculation in the inner loop
        jitterPos = partial + (coord.get_v() * length / q_xi);
        lightRayDir = jitterPos - point;// direction from point to light
        if (!sc.anyHit(Ray(point, lightRayDir), 0.0001f, 1.0f, depth)) {
          directions.push_back(lightRayDir.normalize());// must normalize before sending to shader
          intensities.push_back(subIntensity);
        }
      }
    }
  } else {  // no rpp - just use center of area light
    auto lightPos = position + (coord.get_u() * width / 2) + (coord.get_v() * length / 2);
    auto lightRayDir = lightPos - point;// direction from point to light
    if (!sc.anyHit(Ray(point, lightRayDir), 0.0001f, 1.0f, depth)) {
      directions.push_back(lightRayDir.normalize());// must normalize before sending to shader
      intensities.push_back(subIntensity);
    }
  }
}

}// namespace renderer