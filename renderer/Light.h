#pragma once
#include <vector>
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
   * @brief Adds any lights visible from the given point to the given direction and intensity vectors
   * @param point The point
   * @param depth The current recursion depth
   * @param sc The scene
   * @param directions A vector of directions from the point toward visible lights
   * @param intensities A vector of intensities for those lights
  */
  virtual void getLightSamples(Vector3D point, int depth, SceneContainer &sc, std::vector<Vector3D> &directions, std::vector<Vector3D> &intensities) = 0;

protected:
  Vector3D position, intensity;
};
}// namespace renderer