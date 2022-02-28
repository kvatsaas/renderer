#include "WhittedRayTracer.h"
#include "HitStructure.h"

namespace renderer {

void WhittedRayTracer::render(Framebuffer &fb, SceneContainer sc, int camIndex, const float max_t)
{
  auto &shapes = sc.getShapes();
  auto camPtr = sc.getCameras()[camIndex];
  for (int i = 0; i < fb.getWidth(); i++) {
    for (int j = 0; j < fb.getHeight(); j++) {

      HitStructure h;
      float tmin = 1.0;
      float tmax = max_t;
      bool hitOccurred = false;
      Ray r;
      camPtr->generateRay(i, j, r);

      for (int s = 0; s < shapes.size(); s++) {
        Shape *sPtr = shapes[s];
        if (sPtr->closestHit(r, tmin, tmax, h))
          hitOccurred = true;
      }

      if (hitOccurred) {
        fb.setPixelColor(i, j, h.getShader()->apply(h, sc));
      }
      else
        fb.setPixelColor(i, j, sc.getBGColor());
    }
  }
}

}// namespace renderer