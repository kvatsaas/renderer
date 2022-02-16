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
#include "Triangle.h"
#include "HitStructure.h"

using namespace renderer;

void raytraceTriangle(Triangle *t_ptr, int nx, int ny, std::string outfile)
{
  Framebuffer fb(nx, ny);
  Vector3D U(1, 0, 0), V(0, 1, 0), W(0, 0, 1);
  Vector3D bgdColor(0, 1, 0);
  float focalLength = 1.0;
  float imagePlaneWidth = 0.5;
  float imagePlaneHeight = 0.5;
  float leftIP = -imagePlaneWidth / 2.0;
  float rightIP = imagePlaneWidth / 2.0;
  float bottomIP = -imagePlaneHeight / 2.0;
  float topIP = imagePlaneHeight / 2.0;
  float tmax = 100.0;
  HitStructure h;

  for (int i = 0; i < nx; i++)
    for (int j = 0; j < ny; j++) {
      Ray r;
      Vector3D origin(0.0, 0.0, 0.0);
      r.setOrigin(origin);

      // this will only work for a square image... make sure to check types!
      float u = leftIP + (rightIP - leftIP) * (i + 0.5) / nx;
      float v = bottomIP + (topIP - bottomIP) * (j + 0.5) / ny;
      auto dir = Vector3D(-1.0 * focalLength * W + u * U + v * V);
      r.setDirection(dir);

      if (t_ptr->closestHit(r, focalLength, tmax, h))
        fb.setPixelColor(i, j, t_ptr->getColor());
      else
        fb.setPixelColor(i, j, bgdColor);
    }

  fb.exportAsPNG(outfile);
}

int main(int argc, char *argv[])
{
  int startTime, endTime;
  boost::progress_timer ptimer;
  Triangle *t_ptr = new Triangle(Vector3D(-1.0, -1.0, -5.0), Vector3D(1.0, -1.0, -5.0), Vector3D(0.0, 1.0, -5.0), Vector3D(0, 0, 1));

  startTime = ptimer.elapsed();

  raytraceTriangle(t_ptr, 400, 400, "t_400.png");

  endTime = ptimer.elapsed();
  std::cout << "400x400 rendering time: " << endTime - startTime << std::endl;
  startTime = ptimer.elapsed();

  raytraceTriangle(t_ptr, 40, 40, "t_40.png");

  endTime = ptimer.elapsed();
  std::cout << "40x40 rendering time: " << endTime - startTime << std::endl;

  exit(EXIT_SUCCESS);
}
