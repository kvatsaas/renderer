#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include <boost/progress.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

//#include "png++/png.hpp"

#include "WhittedRayTracer.h"
#include "Framebuffer.h"
#include "SceneContainer.h"
#include "Ray.h"
#include "Triangle.h"
#include "Sphere.h"
#include "PerspectiveCamera.h"

using namespace renderer;

int main(int argc, char *argv[])
{
  double startTime, endTime;
  boost::progress_timer ptimer;

  int width = 136 / 4;
  int height = 166 / 4;

  auto raytracer = WhittedRayTracer();
  auto fb = Framebuffer(width, height);
  auto sc = SceneContainer();
  auto bgColor = Vector3D(0.75, 0.75, 0.75);

  sc.addShape(
    new Triangle(
      Vector3D(-1.0, -1.25, -5.0),
      Vector3D(0.0, -1.25, -5.0),
      Vector3D(-1.0, -0.25, -5.0),
      Vector3D(1, 0, 0)));

  sc.addShape(
    new Sphere(
      Vector3D(-0.3, 0.7, -5),
      0.5,
      Vector3D(0, 1.2, 0)));

  sc.addShape(
    new Triangle(
      Vector3D(0.2, 0.1, -5.0),
      Vector3D(1.1, 0.1, -5.0),
      Vector3D(0.2, -0.8, -5.0),
      Vector3D(0, 0, 1)));

  sc.addShape(
    new Triangle(
      Vector3D(1.1, -0.8, -5.0),
      Vector3D(1.1, 0.1, -5.0),
      Vector3D(0.2, -0.8, -5.0),
      Vector3D(0, 0, 1)));

  Camera *camPtr = new PerspectiveCamera("cam", Vector3D(), CoordSys(), 1.0, 0.5, width, height);

  startTime = ptimer.elapsed();

  raytracer.render(fb, sc.getShapes(), camPtr, bgColor);
  fb.exportAsPNG("missing.png");

  endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
  exit(EXIT_SUCCESS);
}
