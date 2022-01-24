#ifndef _FRAMEBUFFER
#define _FRAMEBUFFER

#include <vector>
#include "Vector3D.h"

namespace renderer {

class Framebuffer
{

public:
  Framebuffer();
  Framebuffer(int w, int h);

  void setPixelColor(int row, int col, Vector3D rgb);

  Vector3D &getPixelColor(int row, int col);

  int getWidth();

  int getHeight();

private:
  int m_width;
  int m_height;
  std::vector<Vector3D> m_pixels;

};

}

#endif