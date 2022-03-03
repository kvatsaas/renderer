#include "OrthographicCamera.h"

namespace renderer {

OrthographicCamera::OrthographicCamera()
  : l(-0.25), r(0.25), b(-0.25), t(.25), nx(100), ny(100)
{
  name = "default";
  position = Vector3D(0.0, 0.0, 0.0);
  coord = CoordSys();
}

OrthographicCamera::OrthographicCamera(std::string camName, Vector3D pos, CoordSys cs, float width, float height, float n_x, float n_y)
{
  r = width / 2.0;
  l = -r;
  nx = n_x;
  ny = n_y;

  float validateHeight = ny / nx * width;
  if (abs(validateHeight - height) / height > 0.01) {
    height = validateHeight;
  }
  t = height / 2.0;
  b = -t;

  name = camName;
  position = pos;
  coord = cs;
}

OrthographicCamera::OrthographicCamera(std::string camName, Vector3D pos, CoordSys cs, float width, float n_x, float n_y)
{
  r = width / 2.0;
  l = -r;
  nx = n_x;
  ny = n_y;

  float height = ny / nx * width;
  t = height / 2.0;
  b = -t;

  name = camName;
  position = pos;
  coord = cs;
}

}// namespace renderer