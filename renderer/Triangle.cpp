#include "Triangle.h"

namespace renderer {
Triangle::Triangle()
  : v_a(0.5, 0.0, 0.0), v_b(-0.5, -0.5, 0.0), v_c(-0.5, 0.5, 0.0),
    a_rgb(1.0, 1.0, 1.0), b_rgb(a_rgb), c_rgb(a_rgb), color(a_rgb)
{
  shaderPtr = new Shader();
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Shader *s)
  : v_a(a), v_b(b), v_c(c),
    a_rgb(1.0, 1.0, 1.0), b_rgb(a_rgb), c_rgb(a_rgb), color(a_rgb)
{
  shaderPtr = s;
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D col, Shader *s = nullptr)
  : v_a(a), v_b(b), v_c(c),
    a_rgb(col), b_rgb(col), c_rgb(col), color(col)
{
  shaderPtr = s;
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D a_col, Vector3D b_col, Vector3D c_col, Shader *s)
  : v_a(a), v_b(b), v_c(c),
    a_rgb(a_col), b_rgb(b_col), c_rgb(c_col)
{
  float col_x = (v_a[0] + v_b[0] + v_c[0]) / 3;
  float col_y = (v_a[1] + v_b[1] + v_c[1]) / 3;
  float col_z = (v_a[2] + v_b[2] + v_c[2]) / 3;
  color = Vector3D(col_x, col_y, col_z);

  shaderPtr = s;
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();
}

bool Triangle::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit)
{
  // The computations below are based on Section 4.2.2 of Fundamentals of Computer Graphics (Marschner/Shirley)
  float t, gamma, beta, M;
  float a, b, c, d, e, f, g, h, i, j, k, l, ei_hf, gf_di, dh_eg, ak_jb, jc_al, bl_kc;
  Vector3D dir = r.getDirection();
  Vector3D orig = r.getOrigin();

  // compute matrix values and derived values - written for readability; compiler should optimize this. probably.
  a = v_a['x'] - v_b['x'];
  b = v_a['y'] - v_b['y'];
  c = v_a['z'] - v_b['z'];
  d = v_a['x'] - v_c['x'];
  e = v_a['y'] - v_c['y'];
  f = v_a['z'] - v_c['z'];
  g = dir['x'];
  h = dir['y'];
  i = dir['z'];
  j = v_a['x'] - orig['x'];
  k = v_a['y'] - orig['y'];
  l = v_a['z'] - orig['z'];

  ei_hf = (e * i) - (h * f);
  gf_di = (g * f) - (d * i);
  dh_eg = (d * h) - (e * g);
  ak_jb = (a * k) - (j * b);
  jc_al = (j * c) - (a * l);
  bl_kc = (b * l) - (k * c);

  M = (a * ei_hf) + (b * gf_di) + (c * dh_eg);

  // compute t
  t = -((f * ak_jb) + (e * jc_al) + (d * bl_kc)) / M;
  if (t < tmin || t > tmax) return false;

  // compute gamma
  gamma = ((i * ak_jb) + (h * jc_al) + (g * bl_kc)) / M;
  if (gamma < 0 || gamma > 1) return false;

  // compute beta
  beta = ((j * ei_hf) + (k * gf_di) + (l * dh_eg)) / M;
  if (beta < 0 || beta > 1 - gamma) return false;

  // hit confirmed
  Vector3D hitPos = r.getOrigin() + (t * r.getDirection());
  Vector3D normalDir = normalDirection;

  // check if it's the correct direction - this might be stupid
  // dot product of normalDir and ray direction is positive if they face the same direction, so reverse
  if (normalDir.dotProduct(r.getDirection()) > 0)
    normalDir *= -1.0;
  Ray normal = Ray(hitPos, normalDir);

  tmax = t;
  hit = HitStructure(shaderPtr, this, r, normal, t);
  return true;
}

const Vector3D &Triangle::getColor()
{
  return color;
}

const Vector3D &Triangle::getNormalDirection()
{
  return normalDirection;
}

}// namespace renderer