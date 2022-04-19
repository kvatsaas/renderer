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
   * @brief Adds any lights visible from the given point to the given direction and intensity vectors
   * @param point The point
   * @param depth The current recursion depth
   * @param sc The scene
   * @param directions A vector of directions from the point toward visible lights
   * @param intensities A vector of intensities for those lights
  */
  virtual void getLightSamples(Vector3D point, int depth, SceneContainer &sc, std::vector<Vector3D> &directions, std::vector<Vector3D> &intensities);
};

}// namespace renderer