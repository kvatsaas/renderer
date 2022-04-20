#pragma once
#include "Light.h"
#include "Shape.h"
#include "CoordSys.h"

namespace renderer {

class AreaLight : public Light
{
public:
  /**
   * @brief Creates a default AreaLight
  */
  AreaLight();

  /**
   * @brief Creates a AreaLight with the given attributes
   * @param p The position of the AreaLight
   * @param i The intensity of the AreaLight
   * @param nv The normal of the AreaLight
   * @param w The width of the AreaLight
   * @param l The length of the AreaLight
   * @param nr The n value for AA, i.e. sqrt(rpp)
  */
  AreaLight(Vector3D p, Vector3D i, Vector3D nv, float w, float l, int nr);

  /**
   * @brief Gets the position of the light
   * @param jitter The optional shadow jitter values. Use boost::none if not using AA
   * @param r The current ray number for antialiasing
   * @return The position of the light
  */
  virtual const Vector3D &getPosition(boost::optional<std::vector<std::pair<float, float>>> jitter, int r = -1) const;

  /**
   * @brief Getter for the area light's coordinate system
   * @return The coordinate system
  */
  CoordSys getCoord();

  /**
   * @brief Determines if the light, or any part of it, is visible to a given ray in the scene
   * @param point The ray
   * @param depth The current recursion depth
   * @param sc The scene
   * @param jitter The optional shadow jitter values
   * @param r The current ray number for antialiasing
   * @return True if the light is visible from the point, false otherwise
  */
  virtual boost::optional<Vector3D> isVisibleFrom(Vector3D point, int depth, SceneContainer &sc, boost::optional<std::vector<std::pair<float, float>>> jitter, int r);

protected:
  Vector3D normal;
  CoordSys coord;
  float width, length;
  int n;

};

}// namespace renderer