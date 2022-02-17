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
#include "NormalShader.h"
#include "Ray.h"
#include "Triangle.h"
#include "Sphere.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"

using namespace renderer;

void multiShapeRender()
{
  double startTime, endTime;
  boost::progress_timer ptimer;

  int width = 136;
  int height = 166;

  auto raytracer = WhittedRayTracer();
  auto fb = Framebuffer(width, height);
  auto sc = SceneContainer();
  auto bgColor = Vector3D(0.75, 0.75, 0.75);

  auto red = new Shader(Vector3D(1, 0, 0));
  auto green = new Shader(Vector3D(0, 1, 0));
  auto blue = new Shader(Vector3D(0, 0, 1));
  auto def = new Shader();

  sc.addShape(
    new Triangle(
      Vector3D(-1.0, -1.25, -5.0),
      Vector3D(0.0, -1.25, -5.0),
      Vector3D(-1.0, -0.25, -5.0),
      red));

  sc.addShape(
    new Sphere(
      Vector3D(-0.3, 0.7, -5),
      0.5,
      green));

  sc.addShape(
    new Triangle(
      Vector3D(0.2, 0.1, -5.0),
      Vector3D(1.1, 0.1, -5.0),
      Vector3D(0.2, -0.8, -5.0),
      blue));

  sc.addShape(
    new Triangle(
      Vector3D(1.1, -0.8, -5.0),
      Vector3D(1.1, 0.1, -5.0),
      Vector3D(0.2, -0.8, -5.0),
      def));

  Camera *camPtr = new PerspectiveCamera("cam", Vector3D(), CoordSys(), 1.0, 0.5, width, height);

  startTime = ptimer.elapsed();

  raytracer.render(fb, sc.getShapes(), camPtr, bgColor);
  fb.exportAsPNG("missing.png");

  endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
}

void normalShaderSphere()
{
  double startTime, endTime;
  boost::progress_timer ptimer;

  int width = 1000;
  int height = 1000;

  auto raytracer = WhittedRayTracer();
  auto fb = Framebuffer(width, height);
  auto sc = SceneContainer();
  auto bgColor = Vector3D();
  auto normal = new NormalShader();
  auto *camPtr = new PerspectiveCamera("cam", Vector3D(), CoordSys(), 1.0, 0.5, width, height);

  sc.addShape(
    new Sphere(
      Vector3D(0.0, 0.0, -5.0),
      1.0,
      normal));

  startTime = ptimer.elapsed();

  raytracer.render(fb, sc.getShapes(), camPtr, bgColor);
  fb.exportAsPNG("nv_sphere.png");

  endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
}

void normalShaderTriangles()
{
  double startTime, endTime;
  boost::progress_timer ptimer;

  int width = 1000;
  int height = 1000;

  auto raytracer = WhittedRayTracer();
  auto fb = Framebuffer(width, height);
  auto sc = SceneContainer();
  auto bgColor = Vector3D();
  auto normal = new NormalShader();
  auto *camPtr = new PerspectiveCamera("cam", Vector3D(), CoordSys(), 1.0, 0.5, width, height);
  //auto *camPtr = new OrthographicCamera("cam", Vector3D(), CoordSys(), 2.0, width, height);

  // could I do this with clever for loops? probably! will I? no!

  // Quadrant I
  {
    sc.addShape(
      new Triangle(
        Vector3D(0.0, 0.0, -5.0),
        Vector3D(0.0, 0.5, -4.5),
        Vector3D(0.5, 0.0, -4.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.5, 0.5, -4.0),
        Vector3D(0.0, 0.5, -4.5),
        Vector3D(0.5, 0.0, -4.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(1.0, 0.0, -5.0),
        Vector3D(1.0, 0.5, -4.5),
        Vector3D(0.5, 0.0, -4.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.5, 0.5, -4.0),
        Vector3D(1.0, 0.5, -4.5),
        Vector3D(0.5, 0.0, -4.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(1.0, 1.0, -5.0),
        Vector3D(1.0, 0.5, -4.5),
        Vector3D(0.5, 1.0, -4.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.5, 0.5, -4.0),
        Vector3D(1.0, 0.5, -4.5),
        Vector3D(0.5, 1.0, -4.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, 1.0, -5.0),
        Vector3D(0.0, 0.5, -4.5),
        Vector3D(0.5, 1.0, -4.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.5, 0.5, -4.0),
        Vector3D(0.0, 0.5, -4.5),
        Vector3D(0.5, 1.0, -4.5),
        normal));
  }
  
  // Quadrant II
  {
    sc.addShape(
      new Triangle(
        Vector3D(0.0, 0.0, -5.0),
        Vector3D(-0.5, 0.0, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, 0.0, -5.0),
        Vector3D(0.0, 0.5, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-1.0, 0.0, -5.0),
        Vector3D(-0.5, 0.0, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-1.0, 0.0, -5.0),
        Vector3D(-1.0, 0.5, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-1.0, 1.0, -5.0),
        Vector3D(-1.0, 0.5, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-1.0, 1.0, -5.0),
        Vector3D(-0.5, 1.0, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, 1.0, -5.0),
        Vector3D(-0.5, 1.0, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, 1.0, -5.0),
        Vector3D(0.0, 0.5, -5.0),
        Vector3D(-0.5, 0.5, -4.0),
        normal));
  }

  // Quadrant III
  {
    sc.addShape(
      new Triangle(
        Vector3D(0.0, 0.0, -5.0),
        Vector3D(0.0, -0.5, -5.5),
        Vector3D(-0.5, 0.0, -5.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-0.5, -0.5, -6.0),
        Vector3D(0.0, -0.5, -5.5),
        Vector3D(-0.5, 0.0, -5.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-1.0, 0.0, -5.0),
        Vector3D(-1.0, -0.5, -5.5),
        Vector3D(-0.5, 0.0, -5.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-0.5, -0.5, -6.0),
        Vector3D(-1.0, -0.5, -5.5),
        Vector3D(-0.5, 0.0, -5.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-1.0, -1.0, -5.0),
        Vector3D(-1.0, -0.5, -5.5),
        Vector3D(-0.5, -1.0, -5.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-0.5, -0.5, -6.0),
        Vector3D(-1.0, -0.5, -5.5),
        Vector3D(-0.5, -1.0, -5.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, -1.0, -5.0),
        Vector3D(0.0, -0.5, -5.5),
        Vector3D(-0.5, -1.0, -5.5),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(-0.5, -0.5, -6.0),
        Vector3D(0.0, -0.5, -5.5),
        Vector3D(-0.5, -1.0, -5.5),
        normal));
  }

  // Quadrant IV
  {
    sc.addShape(
      new Triangle(
        Vector3D(0.0, 0.0, -5.0),
        Vector3D(0.5, 0.0, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, 0.0, -5.0),
        Vector3D(0.0, -0.5, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(1.0, 0.0, -5.0),
        Vector3D(0.5, 0.0, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(1.0, -0.0, -5.0),
        Vector3D(1.0, -0.5, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(1.0, -1.0, -5.0),
        Vector3D(1.0, -0.5, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(1.0, -1.0, -5.0),
        Vector3D(0.5, -1.0, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, -1.0, -5.0),
        Vector3D(0.5, -1.0, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));

    sc.addShape(
      new Triangle(
        Vector3D(0.0, -1.0, -5.0),
        Vector3D(0.0, -0.5, -5.0),
        Vector3D(0.5, -0.5, -6.0),
        normal));
  }

  // optional sphere for funsies
  /*sc.addShape(
    new Sphere(
      Vector3D(0.0, 0.0, -5.0),
      0.75,
      normal));*/

  startTime = ptimer.elapsed();

  raytracer.render(fb, sc.getShapes(), camPtr, bgColor);
  fb.exportAsPNG("nv_triangles.png");

  endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
}

int main(int argc, char *argv[])
{
  multiShapeRender();
  normalShaderSphere();
  normalShaderTriangles();
}
