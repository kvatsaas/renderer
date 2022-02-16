#include <cmath>
#include "Sphere.h"

namespace renderer {

Sphere::Sphere()
  : center(), radius(1.0), color(1, 1, 1) {}

Sphere::Sphere(Vector3D c, float r, Vector3D col)
  : center(c), radius(r), color(col) {}

bool Sphere::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit)
{
  Vector3D d = r.getDirection();
  Vector3D e_c = r.getOrigin() - center; // diff of ray origin and circle center

  float A = d.dotProduct(d);
  float B = (2 * d).dotProduct(e_c);
  float C = e_c.dotProduct(e_c) - (radius * radius);

  float discriminant = (B * B) - (4 * A * C);
  if (discriminant < 0)
    return false;

  float t = (-B - sqrt(discriminant)) / (2 * A);
  if (t < tmin)// if the first hit is in front of the image plane, try the "back" of the sphere
  {
    t = (-B + sqrt(discriminant)) / (2 * A);
    if (t < tmin) return false;
  }
  if (t > tmax) return false;

  //hit confirmed
  // add normal computation

  tmax = t;
  hit = HitStructure(shaderPtr, color, r, r, t);
  return true;
}

Vector3D Sphere::getColor()
{
  return color;
}

}// namespace renderer