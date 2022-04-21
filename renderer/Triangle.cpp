#include <cmath>
#include <iostream>
#include "Triangle.h"

namespace renderer {

Triangle::Triangle()
  : a(0.5, 0.0, 0.0), b(-0.5, -0.5, 0.0), c(-0.5, 0.5, 0.0),
    a_col(1.0, 1.0, 1.0), b_col(a_col), c_col(a_col)
{
  shaderPtr = new Shader();
  normalDirection = (a - b).crossProduct(c - a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

Triangle::Triangle(Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c, Shader *s)
  : a(vertex_a), b(vertex_b), c(vertex_c)
{
  shaderPtr = s;
  normalDirection = (a - b).crossProduct(c - a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

Triangle::Triangle(Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c, Vector3D col, Shader *s)
  : a(vertex_a), b(vertex_b), c(vertex_c),
    a_col(col), b_col(col), c_col(col)
{
  shaderPtr = s;
  normalDirection = (a - b).crossProduct(c - a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

Triangle::Triangle(Vector3D vertex_a, Vector3D vertex_b, Vector3D vertex_c, Vector3D a_rgb, Vector3D b_rgb, Vector3D c_rgb, Shader *s)
  : a(vertex_a), b(vertex_b), c(vertex_c),
    a_col(a_rgb), b_col(b_rgb), c_col(c_rgb)
{
  shaderPtr = s;
  normalDirection = (a - b).crossProduct(c - a).normalize();

  calculateBoundingBox();
  calculateCentroid();
}

void Triangle::setNormals(Vector3D normal_a, Vector3D normal_b, Vector3D normal_c, bool interp)
{
  a_norm = normal_a;
  b_norm = normal_b;
  c_norm = normal_c;
  interpolateNormals = interp;
}

bool Triangle::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth)
{
  if (!bound.intersectClosest(r, depth))
    return false;

  // The computations below are based on Section 4.2.2 of Fundamentals of Computer Graphics (Marschner/Shirley)
  float t, gamma, beta, M;
  float _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, ei_hf, gf_di, dh_eg, ak_jb, jc_al, bl_kc;
  Vector3D dir = r.getDirection();
  Vector3D orig = r.getOrigin();

  // compute matrix values and derived values - written for readability; compiler should optimize this. probably.
  _a = a['x'] - b['x'];
  _b = a['y'] - b['y'];
  _c = a['z'] - b['z'];
  _d = a['x'] - c['x'];
  _e = a['y'] - c['y'];
  _f = a['z'] - c['z'];
  _g = dir['x'];
  _h = dir['y'];
  _i = dir['z'];
  _j = a['x'] - orig['x'];
  _k = a['y'] - orig['y'];
  _l = a['z'] - orig['z'];

  ei_hf = (_e * _i) - (_h * _f);
  gf_di = (_g * _f) - (_d * _i);
  dh_eg = (_d * _h) - (_e * _g);
  ak_jb = (_a * _k) - (_j * _b);
  jc_al = (_j * _c) - (_a * _l);
  bl_kc = (_b * _l) - (_k * _c);

  M = (_a * ei_hf) + (_b * gf_di) + (_c * dh_eg);

  // compute t
  t = -((_f * ak_jb) + (_e * jc_al) + (_d * bl_kc)) / M;
  if (t < tmin || t > tmax) return false;

  // compute gamma
  gamma = ((_i * ak_jb) + (_h * jc_al) + (_g * bl_kc)) / M;
  if (gamma < 0 || gamma > 1) return false;

  // compute beta
  beta = ((_j * ei_hf) + (_k * gf_di) + (_l * dh_eg)) / M;
  if (beta < 0 || beta > 1 - gamma) return false;

  // hit confirmed
  Vector3D hitPos = r.getOrigin() + (t * r.getDirection());
  Vector3D normalDir;
  if (interpolateNormals) {
    float alpha = 1 - beta - gamma;
    normalDir = alpha * a_norm + beta * b_norm + gamma * c_norm;
  } else {
    normalDir = normalDirection;
  }

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
  if (!bound.intersectAny(r, depth))
    return false;

  // The computations below are based on Section 4.2.2 of Fundamentals of Computer Graphics (Marschner/Shirley)
  float t, gamma, beta, M;
  float _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, ei_hf, gf_di, dh_eg, ak_jb, jc_al, bl_kc;
  Vector3D dir = r.getDirection();
  Vector3D orig = r.getOrigin();

  // compute matrix values and derived values - written for readability; compiler should optimize this. probably.
  _a = a['x'] - b['x'];
  _b = a['y'] - b['y'];
  _c = a['z'] - b['z'];
  _d = a['x'] - c['x'];
  _e = a['y'] - c['y'];
  _f = a['z'] - c['z'];
  _g = dir['x'];
  _h = dir['y'];
  _i = dir['z'];
  _j = a['x'] - orig['x'];
  _k = a['y'] - orig['y'];
  _l = a['z'] - orig['z'];

  ei_hf = (_e * _i) - (_h * _f);
  gf_di = (_g * _f) - (_d * _i);
  dh_eg = (_d * _h) - (_e * _g);
  ak_jb = (_a * _k) - (_j * _b);
  jc_al = (_j * _c) - (_a * _l);
  bl_kc = (_b * _l) - (_k * _c);

  M = (_a * ei_hf) + (_b * gf_di) + (_c * dh_eg);

  // compute t
  t = -((_f * ak_jb) + (_e * jc_al) + (_d * bl_kc)) / M;
  if (t < tmin || t > tmax) return false;

  // compute gamma
  gamma = ((_i * ak_jb) + (_h * jc_al) + (_g * bl_kc)) / M;
  if (gamma < 0 || gamma > 1) return false;

  // compute beta
  beta = ((_j * ei_hf) + (_k * gf_di) + (_l * dh_eg)) / M;
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
      alpha = implicitLine(x, y, b, c) / implicitLine(a['x'], a['y'], b, c);
      beta = implicitLine(x, y, a, c) / implicitLine(b['x'], b['y'], a, c);
      gamma = implicitLine(x, y, a, b) / implicitLine(c['x'], c['y'], a, b);

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

  xmin = std::min(a['x'], std::min(b['x'], c['x']));
  ymin = std::min(a['y'], std::min(b['y'], c['y']));
  zmin = std::min(a['z'], std::min(b['z'], c['z']));

  xmax = std::max(a['x'], std::max(b['x'], c['x']));
  ymax = std::max(a['y'], std::max(b['y'], c['y']));
  zmax = std::max(a['z'], std::max(b['z'], c['z']));

  bound = AABoundingBox(
    Vector3D(xmin, ymin, zmin),
    Vector3D(xmax, ymax, zmax));
}

void Triangle::calculateCentroid()
{
  //not 100% sure on this
  center = (a + b + c) / 3;
}

float implicitLine(float x, float y, Vector3D v0, Vector3D v1)
{
  return (v0['y'] - v1['y']) * x + (v1['x'] - v0['x']) * y + v0['x'] * v1['y'] - v1['x'] * v0['y'];
}

}// namespace renderer