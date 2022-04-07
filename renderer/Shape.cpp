#include "Shape.h"

namespace renderer {

Shape::Shape()
{
  shaderPtr = nullptr;
}

void Shape::setShader(Shader *s)
{
  shaderPtr = s;
}

void Shape::setName(std::string s)
{
  name = s;
}

void Shape::setBoundingBox(AABoundingBox &b)
{
  bound = b;
}

void Shape::setVisibleDepthBounds(int min, int max)
{
  bound.setVisibleDepthBounds(min, max);
}

void Shape::setShadowDepthBounds(int min, int max)
{
  bound.setShadowDepthBounds(min, max);
}

const Shader *Shape::getShader() const
{
  return shaderPtr;
}

const std::string &Shape::getName() const
{
  return name;
}

AABoundingBox &Shape::getBoundingBox()
{
  return bound;
}

Vector3D Shape::getCenter() const
{
  return center;
}

}// namespace renderer