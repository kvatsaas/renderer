#include "OrthographicCamera.h"

namespace renderer {

OrthographicCamera::OrthographicCamera()
  : l(-0.25), r(0.25), b(-0.25), t(.25), nx(100), ny(100)
{
  name = "default";
  position = Vector3D(0.0, 0.0, 0.0);
  coord = CoordSys();
  gaze = coord.get_w() * -1.0;
}

OrthographicCamera::OrthographicCamera(std::string camName, Vector3D pos, CoordSys cs, float width, float height, float n_x, float n_y)
  : r(width / 2), l(-r), t(height / 2), b(-t), nx(n_x), ny(n_y)
{
  name = camName;
  position = pos;
  coord = cs;
  gaze = coord.get_w() * -1.0;
}

}// namespace renderer