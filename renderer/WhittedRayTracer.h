#pragma once
#include "Renderer.h"

namespace renderer {

class WhittedRayTracer : public Renderer
{
public:
  void render(Framebuffer &fb, const std::vector<Shape *> shapes, Camera *camPtr, const Vector3D &bgColor = Vector3D(), const float tmax = std::numeric_limits<float>::max());
};

}// namespace renderer