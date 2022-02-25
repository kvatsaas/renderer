#include "Shape.h"

namespace renderer {

Shape::Shape()
{
  shaderPtr = new Shader();
}

void Shape::setShader(Shader *s)
{
  shaderPtr = s;
}

void Shape::setName(std::string s)
{
  name = s;
}

const Shader *Shape::getShader() const
{
  return shaderPtr;
}

const std::string &Shape::getName() const
{
  return name;
}

}// namespace renderer