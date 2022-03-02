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
#include "jsonParser.cpp"
#include "../src/handleGraphicsArgs.h"

using namespace renderer;

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);
  boost::progress_timer ptimer;
  float startTime, endTime;

  auto raytracer = WhittedRayTracer();
  auto fb = Framebuffer(args.width, args.height);
  auto sc = SceneContainer(args.width, args.height);
  if (args.isSet("recursionDepth"))
    sc.setMaxDepth(args.recursionDepth);

  startTime = ptimer.elapsed();
  parseJSONData(args.inputFileName, sc);
  endTime = ptimer.elapsed();
  std::cout << "JSON parsing time: " << endTime - startTime << std::endl;

  startTime = ptimer.elapsed();
  raytracer.render(fb, sc, 0);
  endTime = ptimer.elapsed();
  std::cout << "Render time: " << endTime - startTime << std::endl;

  startTime = ptimer.elapsed();
  fb.exportAsPNG(args.outputFileName);
  endTime = ptimer.elapsed();
  std::cout << "Export time: " << endTime - startTime << std::endl;
}
