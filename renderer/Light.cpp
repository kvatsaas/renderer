#include "Light.h"
#include "SceneContainer.h"

namespace renderer {

const Vector3D &Light::getPosition(boost::optional<std::vector<std::pair<float, float>>> jitter, int r) const
{
  return position;
}

const Vector3D &Light::getIntensity() const
{
  return intensity;
}

}// namespace renderer