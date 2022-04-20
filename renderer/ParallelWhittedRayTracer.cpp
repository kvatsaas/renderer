#include <thread>
#include <ppl.h>
#include "ParallelWhittedRayTracer.h"

using namespace concurrency;

namespace renderer {

ParallelWhittedRayTracer::ParallelWhittedRayTracer(int threads)
{
  if (threads > 0)
    threadCount = threads;
  else
    threadCount = std::thread::hardware_concurrency();
}

void ParallelWhittedRayTracer::render(Framebuffer &fb, SceneContainer sc, int camIndex, const float max_t)
{
  auto camPtr = sc.getCameras()[camIndex];

  parallel_for(int(0), fb.getWidth(), [&](int i) {
    for (int j = 0; j < fb.getHeight(); j++) {
      Ray r;
      camPtr->generateRay(i, j, r);
      fb.setPixelColor(i, j, sc.rayColor(r, 1.0, max_t, 0));
    }
  });
}

void ParallelWhittedRayTracer::renderAA(Framebuffer &fb, SceneContainer sc, int camIndex, int rpp, const float max_t)
{
  int n = sqrt(rpp);
  auto camPtr = sc.getCameras()[camIndex];
  parallel_for(int(0), fb.getWidth(), [&](int i) {
    auto jitterAA = std::vector<std::pair<float, float>>();
    auto jitterShadows = std::vector<std::pair<float, float>>();
    for (int j = 0; j < fb.getHeight(); j++) {
      generateJitter(jitterAA, jitterShadows, rpp);
      auto rays = std::vector<Ray>();
      camPtr->generateSampleRays(i, j, n, jitterAA, rays);
      fb.setPixelColor(i, j, sc.rayColor(rays, 1.0, max_t, 0, jitterShadows));
    }
  });
}

}// namespace renderer
