#include "CoordSys.h"

namespace renderer {

CoordSys::CoordSys()
  : u(1, 0, 0), v(0, 1, 0), w(0, 0, 1) {}

CoordSys::CoordSys(const Vector3D &u, const Vector3D &v, const Vector3D &w)
  : u(u), v(v), w(w) {}

CoordSys::CoordSys(const Vector3D &gazeDirection) 
: u(gazeDirection[0], 0.0, 0.0), v(0.0, gazeDirection[1], 0.0), w(0.0, 0.0, gazeDirection[2]) {}

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