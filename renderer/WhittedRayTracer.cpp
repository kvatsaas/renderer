#include "WhittedRayTracer.h"
#include "HitStructure.h"

namespace renderer {

void WhittedRayTracer::render(Framebuffer &fb, const std::vector<Shape *> shapes, Camera *camPtr, const Vector3D &bgColor, const float max_t)
{
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

      if (hitOccurred)
        fb.setPixelColor(i, j, h.getColor());
      else
        fb.setPixelColor(i, j, bgColor);
    }
  }
}

}// namespace renderer