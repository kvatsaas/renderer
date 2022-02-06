#include "PerspectiveCamera.h"

namespace renderer {
PerspectiveCamera::PerspectiveCamera()
  : focalLength(1.0), l(-0.25), r(0.25), b(-0.25), t(.25), nx(20), ny(20)
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