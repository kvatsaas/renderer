#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include <boost/progress.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

//#include "png++/png.hpp"

#include "Framebuffer.h"

using namespace renderer;

int main(int argc, char *argv[])
{
  int width = 1000;
  int height = 1000;
  auto fb = Framebuffer(width, height);
  float part = fb.getHeight() / 3;

  auto c0 = Vector3D(242, 96, 161) / 255;
  auto c1 = Vector3D(255, 223, 60) / 255;
  auto c2 = Vector3D(60, 204, 180) / 255;
  auto c3 = Vector3D(217, 43, 48) / 255;

  for (auto j = 0; j < (int)part; j++) {
    auto color = c0 * (1 - j / part) + c1 * (j / part);
    for (auto i = 0; i < fb.getWidth(); i++) {
      fb.setPixelColor(i, j, color);
    }
  }
  for (auto j = (int)part; j < (int)(2 * part); j++) {
    auto color = c1 * (1 - (j - (int)part) / part) + c2 * ((j - part) / part);
    for (auto i = 0; i < fb.getWidth(); i++) {
      fb.setPixelColor(i, j, color);
    }
  }
  for (auto j = (int)(2 * part); j < fb.getHeight(); j++) {
    auto color = c2 * (1 - (j - (int)(2 * part)) / part) + c3 * ((j - (int)(2 * part)) / part);
    for (auto i = 0; i < fb.getWidth(); i++) {
      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG("colorramp.png");
}