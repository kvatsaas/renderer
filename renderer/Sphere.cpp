#include <cmath>
#include "Sphere.h"

namespace renderer {

Sphere::Sphere()
  : center(), radius(1.0), color(1, 1, 1)
{
  shaderPtr = new Shader();
}

Sphere::Sphere(Vector3D c, float r, Shader *s, Vector3D col)
  : center(c), radius(r), color(col)
{
  shaderPtr = s;
}

bool Sphere::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit)
{
  Vector3D d = r.getDirection();
  Vector3D e_c = r.getOrigin() - center;// diff of ray origin and circle center

  float A = d.dotProduct(d);
  float B = (2 * d).dotProduct(e_c);
  float C = e_c.dotProduct(e_c) - (radius * radius);

  float discriminant = (B * B) - (4 * A * C);
  if (discriminant < 0)
    return false;

  bool frontHit = true; // keep track for normal computation
  float t = (-B - sqrt(discriminant)) / (2 * A);
  if (t < tmin)// if the first hit is in front of the image plane, try the "back" of the sphere
  {
    t = (-B + sqrt(discriminant)) / (2 * A);
    if (t < tmin) return false;
    frontHit = false;
  }
  if (t > tmax) return false;

  //hit confirmed, compute normal
  Vector3D hitPoint = r.getOrigin() + (t * r.getDirection());
  Vector3D normalDir;
  if (frontHit)
    normalDir = (hitPoint - center) / radius;
  else
    normalDir = (center - hitPoint) / radius;
  Ray normal = Ray(hitPoint, normalDir);

  tmax = t;
  hit = HitStructure(shaderPtr, color, r, normal, t);
  return true;
}

Vector3D Sphere::getColor()
{
  return color;
}

}// namespace renderer