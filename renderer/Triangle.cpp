#include "Triangle.h"

namespace renderer {
Triangle::Triangle()
  : v_a(0.5, 0.0, 0.0), v_b(-0.5, -0.5, 0.0), v_c(-0.5, 0.5, 0.0),
    a_rgb(1.0, 1.0, 1.0), b_rgb(a_rgb), c_rgb(a_rgb), color(a_rgb) {}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c)
  : v_a(a), v_b(b), v_c(c),
    a_rgb(1.0, 1.0, 1.0), b_rgb(a_rgb), c_rgb(a_rgb), color(a_rgb) {}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D col)
  : v_a(a), v_b(b), v_c(c),
    a_rgb(col), b_rgb(col), c_rgb(col), color(col) {}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D a_col, Vector3D b_col, Vector3D c_col)
  : v_a(a), v_b(b), v_c(c),
    a_rgb(a_col), b_rgb(b_col), c_rgb(c_col)
{
  float col_x = (v_a[0] + v_b[0] + v_c[0]) / 3;
  float col_y = (v_a[1] + v_b[1] + v_c[1]) / 3;
  float col_z = (v_a[2] + v_b[2] + v_c[2]) / 3;
  color = Vector3D(col_x, col_y, col_z);
}

bool Triangle::closestHit(const Ray &r, const float focalLength)
{
  // The computations below are based on Section 4.2.2 of Fundamentals of Computer Graphics (Marschner/Shirley)
  float t, gamma, beta, M;
  float a, b, c, d, e, f, g, h, i, j, k, l, ei_hf, gf_di, dh_eg, ak_jb, jc_al, bl_kc;
  Vector3D dir = r.getDirection();
  Vector3D orig = r.getOrigin();

  // compute matrix values and derived values - written for readability; compiler should optimize this. probably.
  a = v_a[0] - v_b[0];
  b = v_a[1] - v_b[1];
  c = v_a[2] - v_b[2];
  d = v_a[0] - v_c[0];
  e = v_a[1] - v_c[1];
  f = v_a[2] - v_c[2];
  g = dir[0];
  h = dir[1];
  i = dir[2];
  j = v_a[0] - orig[0];
  k = v_a[1] - orig[1];
  l = v_a[2] - orig[2];

  ei_hf = (e * i) - (h * f);
  gf_di = (g * f) - (d * i);
  dh_eg = (d * h) - (e * g);
  ak_jb = (a * k) - (j * b);
  jc_al = (j * c) - (a * l);
  bl_kc = (b * l) - (k * c);

  M = (a * ei_hf) + (b * gf_di) + (c * dh_eg);

  // compute t
  t = -((f * ak_jb) + (e * jc_al) + (d * bl_kc)) / M;
  if (t < focalLength) return false;

  // compute gamma
  gamma = ((i * ak_jb) + (h * jc_al) + (g * bl_kc)) / M;
  if (gamma < 0 || gamma > 1) return false;

  // compute beta
  beta = ((j * ei_hf) + (k * gf_di) + (l * dh_eg)) / M;
  if (beta < 0 || beta > 1 - gamma) return false;

  return true;
}

Vector3D Triangle::getColor()
{
  return color;
}

}// namespace renderer