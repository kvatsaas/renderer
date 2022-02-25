#pragma once
#include "Renderer.h"

namespace renderer {

class WhittedRayTracer : public Renderer
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
  void render(Framebuffer &fb, SceneContainer sc, int camIndex, const float max_t = std::numeric_limits<float>::max());
};

}// namespace renderer