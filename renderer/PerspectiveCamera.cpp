#include "PerspectiveCamera.h"

namespace renderer {
PerspectiveCamera::PerspectiveCamera()
  : focalLength(1.0), l(-1.0), r(1.0), b(-1.0), t(1.0), nx(20), ny(20)
{
  name = "default";
  position = Vector3D(0.0, 0.0, 0.0);
  coord = CoordSys();
  gaze = coord.get_w() * -1.0;
}
PerspectiveCamera::PerspectiveCamera(std::string camName, Vector3D pos, CoordSys cs, float fl, float width, float height, float n_x, float n_y)
  : focalLength(fl), r(width / 2), l(-r), t(height / 2), b(-t), nx(n_x), ny(n_y)
{
  name = camName;
  position = pos;
  coord = cs;
  gaze = coord.get_w() * -1.0;
}
}// namespace renderer