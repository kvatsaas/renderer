#include "HitStructure.h"

namespace renderer {

HitStructure::HitStructure()
  : shaderPtr(nullptr), shapePtr(nullptr), hit(), normal(), t(0.0) {}

HitStructure::HitStructure(Shader *s, Shape *sp, Ray h, Ray n, float t)
  : shaderPtr(s), shapePtr(sp), hit(h), normal(n), t(t) {}

const Shader *HitStructure::getShader() const
{
  return shaderPtr;
}

const Shape *HitStructure::getShape() const
{
  return shapePtr;
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