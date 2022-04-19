#include "AreaLight.h"

namespace renderer {
AreaLight::AreaLight()
  : normal(0, -1, 0), width(1), length(1)
{
  intensity = Vector3D(1, 1, 1);
  shapes = std::vector<Shape *>();

  normal.normalize();
  coord = CoordSys(normal);

  // position is the lower left corner of the light, i.e. min point
  position = Vector3D() - (coord.get_u() * width / 2) - (coord.get_v() * length / 2);
}
AreaLight::AreaLight(Vector3D p, Vector3D i, Vector3D n, float w, float l)
  : normal(n), width(w), length(l)
{
  intensity = i;
  shapes = std::vector<Shape *>();

  normal.normalize();
  coord = CoordSys(normal);

  // position is the lower left corner of the light, i.e. min point
  position = p - (coord.get_u() * width / 2) - (coord.get_v() * length / 2);
}
void AreaLight::addShape(Shape *s)
{
  shapes.push_back(s);
}
std::vector<Shape *> AreaLight::getShapes()
{
  return shapes;
}
bool AreaLight::isVisibleFrom(Vector3D point, int depth, SceneContainer &sc)
{
  //for now, just assume all area lights are visible
  return true;
}
}// namespace renderer