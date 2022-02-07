#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include <boost/progress.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

//#include "png++/png.hpp"

#include "Framebuffer.h"
#include "Ray.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"

using namespace renderer;

int main(int argc, char *argv[])
{
  int width = 400;
  int height = 400;
  Framebuffer fb(width, height);
  Camera *camPtr = new PerspectiveCamera(); // Use only default

  int startTime, endTime;
  boost::progress_timer ptimer;
  startTime = ptimer.elapsed();

  for (auto j = 0; j < fb.getHeight(); j++) {
    for (auto i = 0; i < fb.getWidth(); i++) {

      Ray r;
      camPtr->generateRay(i, j, r);

      // turn ray direction into a color
      Vector3D rayDirColor = ((r.getDirection().unitVector() + Vector3D(1, 1, 1)) * 0.5);

      fb.setPixelColor(i, j, rayDirColor);
    }
  }

  fb.exportAsPNG("rayvis_default.png");

  endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;

  exit(EXIT_SUCCESS);
}