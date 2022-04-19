#include "Light.h"
#include "SceneContainer.h"

namespace renderer {

const Vector3D &Light::getPosition() const
{
  return position;
}

const Vector3D &Light::getIntensity() const
{
  return intensity;
}

}// namespace renderer