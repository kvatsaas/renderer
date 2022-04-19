#pragma once
#include "Vector3D.h"

namespace renderer {

class SceneContainer;// forward declaration

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

  /**
   * @brief Determines if the light, or any part of it, is visible from the given point in the given scene
   * @param point The point
   * @param depth The current recursion depth
   * @param sc The scene
   * @return True if the light is visible from the point, false otherwise
  */
  virtual bool isVisibleFrom(Vector3D point, int depth, SceneContainer &sc) = 0;

protected:
  Vector3D position, intensity;
};
}// namespace renderer