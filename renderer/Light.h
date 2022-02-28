#pragma once
#include "Vector3D.h"

namespace renderer {

class Light
{
public:
  /**
   * @brief Gets the position of the light
   * @return The position of the light
  */
  const Vector3D &getPosition() const;

  /**
   * @brief Gets the intensity of the light
   * @return The intensity of the light
  */
  const Vector3D &getIntensity() const;

protected:
  Vector3D position, intensity;
};
}// namespace renderer