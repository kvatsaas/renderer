#define DEBUG 0
#include <iostream>
#include "WhittedRayTracer.h"
#include "HitStructure.h"

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

}// namespace renderer