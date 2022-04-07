#include <cmath>
#include "Sphere.h"

namespace renderer {

Sphere::Sphere()
  : radius(1.0), color(1, 1, 1)
{
  center = Vector3D();
  shaderPtr = new Shader();
  bound = AABoundingBox(
    Vector3D(
      center['x'] - radius,
      center['y'] - radius,
      center['z'] - radius),
    Vector3D(
      center['x'] + radius,
      center['y'] + radius,
      center['z'] + radius));
  color = Vector3D();
}

Sphere::Sphere(Vector3D c, float r, Shader *s, Vector3D col)
  : radius(r), color(col)
{
  center = c;
  shaderPtr = s;
  bound = AABoundingBox(
    Vector3D(
      center['x'] - radius,
      center['y'] - radius,
      center['z'] - radius),
    Vector3D(
      center['x'] + radius,
      center['y'] + radius,
      center['z'] + radius));
  color = Vector3D();
}

bool Sphere::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth)
{
  if (!bound.intersectClosest(r, depth))
    return false;

  Vector3D d = r.getDirection();
  Vector3D e_c = r.getOrigin() - center;// diff of ray origin and circle center

  float A = d.dotProduct(d);
  float B = (2 * d).dotProduct(e_c);
  float C = e_c.dotProduct(e_c) - (radius * radius);

  float discriminant = (B * B) - (4 * A * C);
  if (discriminant < 0)
    return false;

  bool frontHit = true;// keep track for normal computation
  float t = (-B - sqrt(discriminant)) / (2 * A);
  if (t < tmin)// if the first hit is in front of the image plane, try the "back" of the sphere
  {
    t = (-B + sqrt(discriminant)) / (2 * A);
    if (t < tmin) return false;
    frontHit = false;
  }
  if (t > tmax) return false;

  //hit confirmed, compute normal
  Vector3D hitPos = r.getOrigin() + (t * r.getDirection());
  Vector3D normalDir;
  if (frontHit)
    normalDir = (hitPos - center) / radius;
  else
    normalDir = (center - hitPos) / radius;
  Ray normal = Ray(hitPos, normalDir);

  tmax = t;
  hit = HitStructure(shaderPtr, this, r, normal, t);
  return true;
}

bool Sphere::hit(const Ray &r, float tmin, float tmax, int depth)
{
  if (!bound.intersectAny(r, depth))
    return false;

  Vector3D d = r.getDirection();
  Vector3D e_c = r.getOrigin() - center;// diff of ray origin and circle center

  float A = d.dotProduct(d);
  float B = (2 * d).dotProduct(e_c);
  float C = e_c.dotProduct(e_c) - (radius * radius);

  float discriminant = (B * B) - (4 * A * C);
  if (discriminant < 0)
    return false;

  bool frontHit = true;// keep track for normal computation
  float t = (-B - sqrt(discriminant)) / (2 * A);
  if (t < tmin)// if the first hit is in front of the image plane, try the "back" of the sphere
  {
    t = (-B + sqrt(discriminant)) / (2 * A);
    if (t < tmin) return false;
    frontHit = false;
  }
  if (t > tmax)
    return false;
  else
    return true;
}

}// namespace renderer