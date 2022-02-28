#include "PointLight.h"

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

}// namespace renderer