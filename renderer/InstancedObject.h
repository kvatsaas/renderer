#pragma once

#include <memory>
#include "Shape.h"
#include <glm/ext/matrix_float4x4.hpp>

namespace renderer {

class InstancedObject : public Shape
{
  InstancedObject() {}
  InstancedObject(std::shared_ptr<Shape> &robj, glm::mat4 &m, glm::mat4 mInv);

};

}// namespace renderer
