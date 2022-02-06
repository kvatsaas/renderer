#include "PerspectiveCamera.h"

namespace renderer {
PerspectiveCamera::PerspectiveCamera()
  : focalLength(0.5), l(-10), r(10), b(-10), t(10), nx(20), ny(20)
{
  name = "default";
  position = Vector3D(0.0, 0.0, 0.0);
  coord = CoordSys();
}
PerspectiveCamera::PerspectiveCamera(std::string camName, Vector3D pos, CoordSys cs, float fl, float width, float height, float n_x, float n_y)
  : focalLength(fl), r(width / 2), l(-r), t(height / 2), b(-t), nx(n_x), ny(n_y)
{
  name = camName;
  position = pos;
  coord = cs;
}
}// namespace renderer