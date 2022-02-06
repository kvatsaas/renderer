#pragma once
#include "Light.h"
#include "Vector3D.h"

namespace renderer {

class PointLight : public Light
{
public:
  /**
   * @brief Creates a default PointLight at (0, 0, 0) with white light
  */
  PointLight();

  /**
   * @brief Creates a PointLight with the given attributes
   * @param pos The position of the PointLight
   * @param inten The intensity of the PointLight
  */
  PointLight(Vector3D pos, Vector3D inten);

protected:
  Vector3D position, intensity;
};

}// namespace renderer