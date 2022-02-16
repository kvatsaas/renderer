#include "HitStructure.h"

namespace renderer {

HitStructure::HitStructure()
  : shaderPtr(nullptr), color(), hit(), normal(), t(0.0) {}

HitStructure::HitStructure(Shader *s, Vector3D c, Ray h, Ray n, float t)
  : shaderPtr(s), color(c), hit(h), normal(n), t(t) {}

const Shader *HitStructure::getShader() const
{
  return shaderPtr;
}

const Vector3D &HitStructure::getColor() const
{
  return color;
}

const Ray &HitStructure::getHit() const
{
  return hit;
}

const Ray &HitStructure::getNormal() const
{
  return normal;
}

float HitStructure::get_t() const
{
  return t;
}

}// namespace renderer