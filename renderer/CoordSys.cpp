#include "CoordSys.h"

namespace renderer {

CoordSys::CoordSys()
  : u(1, 0, 0), v(0, 1, 0), w(0, 0, 1) {}

CoordSys::CoordSys(const Vector3D &u, const Vector3D &v, const Vector3D &w)
  : u(u), v(v), w(w) {}

CoordSys::CoordSys(const Vector3D& gazeDirection, Vector3D tempUp)
{
  w = (-1.0 * gazeDirection).unitVector();
  if (gazeDirection == tempUp || w == tempUp)
    tempUp = Vector3D(1, 0, 0);
  u = tempUp.crossProduct(w).unitVector();
  v = w.crossProduct(u).unitVector();
}

Vector3D &CoordSys::get_u()
{
  return u;
}

Vector3D &CoordSys::get_v()
{
  return v;
}

Vector3D &CoordSys::get_w()
{
  return w;
}

}// namespace renderer