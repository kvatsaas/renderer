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
   * @param p The position of the PointLight
   * @param i The intensity of the PointLight
  */
  PointLight(Vector3D p, Vector3D i);

  /**
   * @brief Determines if the light, or any part of it, is visible from the given point in the given scene
   * @param point The point
   * @param depth The current recursion depth
   * @param sc The scene
   * @return True if the light is visible from the point, false otherwise
  */
  virtual bool isVisibleFrom(Vector3D point, int depth, SceneContainer &sc);
};

}// namespace renderer