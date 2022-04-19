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
   * @param nr 
  */
  AreaLight(Vector3D p, Vector3D i, Vector3D nv, float w, float l, int nr);

  CoordSys getCoord();

  /**
   * @brief Adds any lights visible from the given point to the given direction and intensity vectors
   * @param point The point
   * @param depth The current recursion depth
   * @param sc The scene
   * @param directions A vector of directions from the point toward visible lights
   * @param intensities A vector of intensities for those lights
  */
  virtual void getLightSamples(Vector3D point, int depth, SceneContainer &sc, std::vector<Vector3D> &directions, std::vector<Vector3D> &intensities);

protected:
  Vector3D normal;
  CoordSys coord;
  float width, length;
  int n = 0;
  Vector3D subIntensity;

  /* HEY IT'S YOU FROM YESTERDAY
  * Generate the jitter points for both raytracing AND shadows, then shuffle the one
  * for shadows so there's no coherence between the two. Maybe stick these in the scene
  * container for later access. See page 332 in the book
  */

};

}// namespace renderer