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

const Shader *Shape::getShader() const
{
  return shaderPtr;
}

}// namespace renderer