#pragma once
#include "Light.h"
#include "Vector3D.h"

namespace renderer {

class PointLight : public Light
{
public:
  PointLight();
  PointLight(Vector3D pos, Vector3D inten);

protected:
  Vector3D position, intensity;
};

}// namespace renderer