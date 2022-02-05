#include "OrthographicCamera.h"

namespace renderer {

OrthographicCamera::OrthographicCamera()
  : l(-10), r(10), b(-10), t(10), nx(20), ny(20) 
{
  name = "default";
  position = Vector3D(0.0, 0.0, 0.0);
  coord = CoordSys();
}

OrthographicCamera::OrthographicCamera(std::string camName, Vector3D pos, CoordSys cs, float left, float right, float bottom, float top, float n_x, float n_y)
  : l(left), r(right), b(bottom), t(top), nx(n_x), ny(n_y)
{
  name = camName;
  position = pos;
  coord = cs;
}

}// namespace renderer