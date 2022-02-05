#pragma once
#include "Vector3D.h"

namespace renderer {

// Coordinate Sys - represent arbitrary 3D bases
// -- could be called OrthonormalBasis
// -- ortho -- means at 90 degrees to each other
// -- normal -- unit length

class CoordSys
{
public:
  CoordSys();
  CoordSys(const Vector3D &u, const Vector3D &v, const Vector3D &w);
  CoordSys(const Vector3D &gazeDirection);

  Vector3D &get_u();
  Vector3D &get_v();
  Vector3D &get_w();

protected:
  // Need to represent each vector of the basis
  Vector3D u, v, w;
};

}// namespace renderer