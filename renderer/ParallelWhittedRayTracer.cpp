#include <iostream>
#include <cmath>
#include <thread>
#include <algorithm>
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
  //std::cout << "Using " << threadCount << " threads";
  //auto threads = std::vector<std::thread>();
  /*int pixelCount = fb.getWidth() * fb.getHeight();
  int threadWork = pixelCount / threadCount;*/

  auto camPtr = sc.getCameras()[camIndex];

  parallel_for(int(0), fb.getWidth(), [&](int i) {
    for (int j = 0; j < fb.getHeight(); j++) {
      Ray r;
      camPtr->generateRay(i, j, r);
      fb.setPixelColor(i, j, sc.rayColor(r, 1.0, max_t, 0));
    }
  });

  // create threads
  //for (int t = 0; t < threadCount; t++) {
  //  threads.push_back(std::thread(std::bind(
  //    [&](const int begin, const int end, const int t) {
  //      for (int i = begin; i < end; i++) {
  //        for (int j = 0; j < fb.getHeight(); j++) {
  //          Ray r;
  //          camPtr->generateRay(i, j, r);
  //          fb.setPixelColor(i, j, sc.rayColor(r, 1.0, max_t, 0));
  //        }
  //      }
  //    },
  //    t * threadWork,
  //    (t + 1) == threadCount ? pixelCount : (t + 1) * threadWork,
  //    t)));
  //}

  //// run threads
  //for (int t = 0; t < threads.size(); t++) {
  //  threads[t].join();
  //}
}

void ParallelWhittedRayTracer::renderAA(Framebuffer &fb, SceneContainer sc, int camIndex, int rpp, const float max_t)
{
  /*std::cout << "Using " << threadCount << " threads";
  auto threads = std::vector<std::thread>();

  int pixelCount = fb.getWidth() * fb.getHeight();*/
  int n = sqrt(rpp);
  auto camPtr = sc.getCameras()[camIndex];
  parallel_for(int(0), fb.getWidth(), [&](int i) {
    for (int j = 0; j < fb.getHeight(); j++) {
      auto rays = std::vector<Ray>();
      camPtr->generateSampleRays(i, j, n, rays);

      auto color = Vector3D();
      for (int r = 0; r < rays.size(); r++)
        color += sc.rayColor(rays[r], 1.0, max_t, 0);
      color /= rpp;

      fb.setPixelColor(i, j, color);
    }
  });

  // create threads
  //for (int t = 0; t < threadCount; t++) {
  //  threads.push_back(std::thread(std::bind(
  //    [&](const int begin, const int end, const int t) {
  //      for (int i = 0; i < fb.getWidth(); i++) {
  //        for (int j = 0; j < fb.getHeight(); j++) {
  //          auto rays = std::vector<Ray>();
  //          camPtr->generateSampleRays(i, j, n, rays);

  //          auto color = Vector3D();
  //          for (int r = 0; r < rays.size(); r++)
  //            color += sc.rayColor(rays[r], 1.0, max_t, 0);
  //          color /= rpp;

  //          fb.setPixelColor(i, j, color);
  //        }
  //      }
  //    },
  //    t * pixelCount / threadCount,
  //    (t + 1) == threadCount ? pixelCount : (t + 1) * pixelCount / threadCount,
  //    t)));
  //}

  //// run threads
  //for (int t = 0; t < threads.size(); t++) {
  //  threads[t].join();
  //}
}

}// namespace renderer
