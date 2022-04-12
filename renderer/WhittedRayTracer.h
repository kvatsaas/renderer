#pragma once
#include "Renderer.h"

namespace renderer {

class WhittedRayTracer : public Renderer
{
public:
  /**
   * @brief Renders an image in the framebuffer for the given scene and camera.
   * @param fb The framebuffer in which to store the rendered image
   * @param sc The scene object
   * @param camIndex The index of the camera from the scene to be used
   * @param max_t The maximum view distance. Defaults to the max value.
  */
  virtual void render(Framebuffer &fb, SceneContainer sc, int camIndex, const float max_t = std::numeric_limits<float>::max());

  /**
   * @brief Renders an image in the framebuffer for the given scene and camera using stratified sampling.
   * @param The framebuffer in which to store the rendered image
   * @param sc The scene object
   * @param camIndex The index of the camera from the scene to be used
   * @param rpp The number of rays per pixel
   * @param max_t The maximum view distance. Defaults to the max value.
  */
  virtual void renderAA(Framebuffer &fb, SceneContainer sc, int camIndex, int rpp, const float max_t = std::numeric_limits<float>::max());
};

}// namespace renderer