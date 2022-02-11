#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

#include <boost/progress.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

//#include "png++/png.hpp"

#include "Framebuffer.h"
#include "Ray.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"

using namespace renderer;

void rayVis(Camera *camPtr, Framebuffer fb)
{
  for (auto j = 0; j < fb.getHeight(); j++) {
    for (auto i = 0; i < fb.getWidth(); i++) {

      Ray r;
      camPtr->generateRay(i, j, r);

      fb.setPixelColor(i, j, r.directionToColor());
    }
  }

  fb.exportAsPNG(camPtr->getName() + ".png");
}

int main(int argc, char *argv[])
{
  int w = 350;
  int h = 250;
  Framebuffer fb(w, h);
  std::vector<Camera *> cameras = {
    new PerspectiveCamera("rayvis_yellow",
      Vector3D(0, 0, 0),
      CoordSys(Vector3D(0, 0, -1)),
      1.0,
      0.5,
      w,
      h),
    new PerspectiveCamera("rayvis_blue",
      Vector3D(0, 0, 0),
      CoordSys(Vector3D(0, 0, 1)),
      1.0,
      0.5,
      w,
      h),
    new PerspectiveCamera("rayvis_pink",
      Vector3D(0, 0, 0),
      CoordSys(Vector3D(1, 0, 0)),
      1.0,
      0.5,
      w,
      h),
    new PerspectiveCamera("rayvis_teal",
      Vector3D(0, 0, 0),
      CoordSys(Vector3D(-1, 0, 0)),
      1.0,
      0.5,
      w,
      h),
    new PerspectiveCamera("rayvis_light",
      Vector3D(-19, 12, 3),
      CoordSys(Vector3D(0, 1, 0)),
      0.15,
      0.5,
      w,
      h),
    new PerspectiveCamera("rayvis_dark",
      Vector3D(-19, 12, 3),
      CoordSys(Vector3D(0, -1, 0)),
      0.15,
      0.5,
      w,
      h),
    new PerspectiveCamera("rayvis_all",
      Vector3D(0, 0, 0),
      CoordSys(Vector3D(0, 0, -1)),
      0.05,
      0.5,
      w,
      h)
  };

  for (int i = 0; i < cameras.size(); i++) {
    rayVis(cameras[i], fb);
  }
}