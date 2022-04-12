#pragma once
#include "Renderer.h"
#include "HitStructure.h"

namespace renderer {

class ParallelWhittedRayTracer : public Renderer
{
public:

  /**
   * @brief Creates a parallel whitted ray tracer with the number of threads to utilize
   * @param threads The number of threads to utilize
  */
  ParallelWhittedRayTracer(int threads);

  /**
   * @brief Renders an image in the framebuffer for the given scene and camera.
   * @param fb The framebuffer in which to store the rendered image
   * @param sc The scene object
   * @param camIndex The index of the camera from the scene to be used
   * @param max_t The maximum view distance. Defaults to the max value.
  */;
  virtual void render(Framebuffer &fb, SceneContainer sc, int camIndex, const float max_t = FLT_MAX);

  /**
   * @brief Renders an image in the framebuffer for the given scene and camera using stratified sampling.
   * @param The framebuffer in which to store the rendered image
   * @param sc The scene object
   * @param camIndex The index of the camera from the scene to be used
   * @param rpp The number of rays per pixel
   * @param max_t The maximum view distance. Defaults to the max value.
  */
  virtual void renderAA(Framebuffer &fb, SceneContainer sc, int camIndex, int rpp, const float max_t = FLT_MAX);

private:
  int threadCount;
};

}// namespace renderer