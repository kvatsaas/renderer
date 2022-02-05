#include "Triangle.h"

namespace renderer {
Triangle::Triangle()
  : a(1.0, 0.0, 0.0), b(0.0, -1.0, 0.0), c(0.0, 1.0, 0.0),
    a_rgb(1.0, 1.0, 1.0), b_rgb(1.0, 1.0, 1.0), c_rgb(1.0, 1.0, 1.0) {}

Triangle::Triangle(Vector3D a_vert, Vector3D b_vert, Vector3D c_vert, Vector3D a_col, Vector3D b_col, Vector3D c_col)
  : a(a_vert), b(b_vert), c(c_vert), a_rgb(a_col), b_rgb(b_col), c_rgb(c_col) {}

bool Triangle::closestHit(const Ray& r) {
  return false;	// TODO
}
}// namespace renderer