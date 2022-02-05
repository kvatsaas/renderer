#include "PointLight.h"

namespace renderer {

PointLight::PointLight()
  : position(0.0, 0.0, 0.0), intensity(1.0, 1.0, 1.0) {}

PointLight::PointLight(Vector3D pos, Vector3D inten)
  : position(pos), intensity(inten) {}

}// namespace renderer