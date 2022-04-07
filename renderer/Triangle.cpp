#include <cmath>
#include <iostream>
#include "Triangle.h"

namespace renderer {
Triangle::Triangle()
  : v_a(0.5, 0.0, 0.0), v_b(-0.5, -0.5, 0.0), v_c(-0.5, 0.5, 0.0),
    a_col(1.0, 1.0, 1.0), b_col(a_col), c_col(a_col)
{
  shaderPtr = new Shader();
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Shader *s)
  : v_a(a), v_b(b), v_c(c),
    a_col(1.0, 1.0, 1.0), b_col(a_col), c_col(a_col)
{
  shaderPtr = s;
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D col, Shader *s)
  : v_a(a), v_b(b), v_c(c),
    a_col(col), b_col(col), c_col(col)
{
  shaderPtr = s;
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D a_rgb, Vector3D b_rgb, Vector3D c_rgb, Shader *s)
  : v_a(a), v_b(b), v_c(c),
    a_col(a_rgb), b_col(b_rgb), c_col(c_rgb)
{
  shaderPtr = nullptr;
  normalDirection = (v_a - v_b).crossProduct(v_c - v_a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

bool Triangle::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth)
{
  if (!bound.intersect(r, depth, true))
    return false;

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

bool Triangle::hit(const Ray &r, float tmin, float tmax, int depth)
{
  if (!bound.intersect(r, depth, false))
    return false;

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
  if (beta < 0 || beta > 1 - gamma)
    return false;
  else
    return true;
}

void Triangle::rasterize2D(Framebuffer &fb)
{
  float alpha, beta, gamma;
  auto minPt = bound.getMinPoint();
  auto maxPt = bound.getMaxPoint();

  for (int y = minPt['y']; y <= maxPt['y']; y++) {
    for (int x = minPt['x']; x <= maxPt['x']; x++) {
      alpha = implicitLine(x, y, v_b, v_c) / implicitLine(v_a['x'], v_a['y'], v_b, v_c);
      beta = implicitLine(x, y, v_a, v_c) / implicitLine(v_b['x'], v_b['y'], v_a, v_c);
      gamma = implicitLine(x, y, v_a, v_b) / implicitLine(v_c['x'], v_c['y'], v_a, v_b);

      if (alpha > 0 && beta > 0 && gamma > 0) {
        fb.setPixelColor(x, y, alpha * a_col + beta * b_col + gamma * c_col);
      }
    }
  }
}

const Vector3D &Triangle::getNormalDirection()
{
  return normalDirection;
}

void Triangle::calculateBoundingBox()
{
  float xmin, xmax, ymin, ymax, zmin, zmax;

  xmin = std::min(v_a['x'], std::min(v_b['x'], v_c['x']));
  ymin = std::min(v_a['y'], std::min(v_b['y'], v_c['y']));
  zmin = std::min(v_a['z'], std::min(v_b['z'], v_c['z']));

  xmax = std::max(v_a['x'], std::max(v_b['x'], v_c['x']));
  ymax = std::max(v_a['y'], std::max(v_b['y'], v_c['y']));
  zmax = std::max(v_a['z'], std::max(v_b['z'], v_c['z']));

  bound = AABoundingBox(
    Vector3D(xmin, ymin, zmin),
    Vector3D(xmax, ymax, zmax));
}

void Triangle::calculateCentroid()
{
  //not 100% sure on this
  center = (v_a + v_b + v_c) / 3;
}

float implicitLine(float x, float y, Vector3D v0, Vector3D v1)
{
  return (v0['y'] - v1['y']) * x + (v1['x'] - v0['x']) * y + v0['x'] * v1['y'] - v1['x'] * v0['y'];
}

}// namespace renderer