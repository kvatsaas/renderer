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
  /**
   * @brief Renders an image in the framebuffer of the given shapes from the view of the given camera. Background color and view distance are optional.
   * @param fb The framebuffer in which to store the rendered image
   * @param shapes The shapes in the scene
   * @param camPtr A pointer to the camera viewing the scene
   * @param bgColor The background color. Defaults to black.
   * @param tmax The maximum view distance. Defaults to the max value.
  */
  virtual void render(Framebuffer &fb, const std::vector<Shape *> shapes, Camera *camPtr, const Vector3D &bgColor = Vector3D(), const float tmax = std::numeric_limits<float>::max()) = 0;
};

}// namespace renderer