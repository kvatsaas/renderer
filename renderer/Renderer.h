#pragma once
#include "Shader.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Framebuffer.h"
#include "SceneContainer.h"
#include "Camera.h"

namespace renderer {

class Renderer
{
public:
  virtual void render(Framebuffer &fb, const std::vector<Shape *> shapes, Camera *camPtr, const Vector3D &bgColor = Vector3D(), const float tmax = std::numeric_limits<float>::max()) = 0;
};

}// namespace renderer