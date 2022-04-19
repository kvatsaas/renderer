#pragma once
#include "Light.h"

#include <vector>
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
   * @param n The normal of the AreaLight
   * @param w The width of the AreaLight
   * @param l The length of the AreaLight
  */
  AreaLight(Vector3D p, Vector3D i, Vector3D n, float w, float l);

  /**
   * @brief Adds a shape to the vector of shapes that comprise this light
   * @param s A pointer to a shape
  */
  void addShape(Shape *s);

  /**
   * @brief Gets the vector of shapes that comprise this light
   * @return The vector of shapes
  */
  std::vector<Shape *> getShapes();

  /**
   * @brief Determines if the light, or any part of it, is visible from the given point in the given scene
   * @param point The point
   * @param depth The current recursion depth
   * @param sc The scene
   * @return True if the light is visible from the point, false otherwise
  */
  virtual bool isVisibleFrom(Vector3D point, int depth, SceneContainer &sc);

private:
  Vector3D normal;
  CoordSys coord;
  float width, length;
  std::vector<Shape *> shapes;
};

}// namespace renderer