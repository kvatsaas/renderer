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
  PointLight(Vector3D p, Vector3D i);
};

}// namespace renderer