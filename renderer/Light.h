#pragma once
#include <vector>
#include <boost/optional/optional.hpp>
#include "Vector3D.h"
#include "Ray.h"

namespace renderer {

class SceneContainer;// forward declaration

class Light
{
public:

  /**
   * @brief Gets the position of the light
   * @param jitter The optional shadow jitter values. Use boost::none if not using AA
   * @param r The current ray number for antialiasing
   * @return The position of the light
  */
  virtual const Vector3D getPosition(boost::optional<std::vector<std::pair<float, float>>> jitter, int r = -1) const;

  /**
   * @brief Gets the intensity of the light
   * @return The intensity of the light
  */
  const Vector3D &getIntensity() const;

  /**
   * @brief Determines if the light, or any part of it, is visible to a given ray in the scene
   * @param point The ray
   * @param depth The current recursion depth
   * @param sc The scene
   * @param jitter The optional shadow jitter values
   * @param r The current ray number for antialiasing
   * @return True if the light is visible from the point, false otherwise
  */
  virtual boost::optional<Vector3D> isVisibleFrom(Vector3D point, int depth, SceneContainer &sc, boost::optional<std::vector<std::pair<float, float>>> jitter, int r) = 0;

protected:
  Vector3D position, intensity;
};
}// namespace renderer