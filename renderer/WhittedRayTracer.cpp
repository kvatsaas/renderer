#include "WhittedRayTracer.h"

#include <iostream>
#include <cmath>
#include <random>

#include "HitStructure.h"
#define DEBUG 0

namespace renderer {

void WhittedRayTracer::render(Framebuffer &fb, SceneContainer sc, int camIndex, const float max_t)
{
  auto camPtr = sc.getCameras()[camIndex];
  for (int i = 0; i < fb.getWidth(); i++) {
    for (int j = 0; j < fb.getHeight(); j++) {
      Ray r;
      camPtr->generateRay(i, j, r);
      fb.setPixelColor(i, j, sc.rayColor(r, 1.0, max_t, 0));
    }

    if (DEBUG) std::cout << i << std::endl;// tracking progress for slow renders
  }
}

void WhittedRayTracer::renderAA(Framebuffer &fb, SceneContainer sc, int camIndex, int rpp, const float max_t)
{
  int n = sqrt(rpp);
  auto camPtr = sc.getCameras()[camIndex];

  auto jitterAA = std::vector<std::pair<float, float>>();
  auto jitterShadows = std::vector<std::pair<float, float>>();

  for (int i = 0; i < fb.getWidth(); i++) {
    for (int j = 0; j < fb.getHeight(); j++) {
      generateJitter(jitterAA, jitterShadows, rpp);
      auto rays = std::vector<Ray>();
      camPtr->generateSampleRays(i, j, n, jitterAA, rays);
      auto color = sc.rayColor(rays, 1.0, max_t, 0, jitterShadows);
      auto grr = color.length();
      fb.setPixelColor(i, j, color);
    }

    if (DEBUG) std::cout << i << std::endl;// tracking progress for slow renders
  }
}

void WhittedRayTracer::generateJitter(std::vector<std::pair<float, float>> &jitterAA, std::vector<std::pair<float, float>> &jitterShadows, int rpp)
{
  // set up thread-safe random number generator
  static thread_local std::random_device rd;
  static thread_local std::mt19937 gen(rd());
  static thread_local std::uniform_real_distribution<> rand(0, 1);

  // clear existing jitter values
  jitterAA.clear();
  jitterShadows.clear();

  // fill with new jitter values
  for (int i = 0; i < rpp; i++) {
    jitterAA.push_back(std::make_pair((float)rand(gen), (float)rand(gen)));
    jitterShadows.push_back(std::make_pair((float)rand(gen), (float)rand(gen)));
  }
  
  /** 
   * shuffle jitterShadows to eliminate coherency between the two
   * I tried to use the built-in std::shuffle but got weird errors,
   * so here's the one from the book instead.
  */
  //shuffle(std::begin(jitterShadows), std::end(jitterShadows), rd());
  for (int i = rpp - 1; i > 0; i--) {
    static thread_local std::uniform_int_distribution<> rand_int(0, i);
    int shuffle = rand_int(gen);
    std::swap(jitterShadows[i], jitterShadows[shuffle]);
  }
}

}// namespace renderer
