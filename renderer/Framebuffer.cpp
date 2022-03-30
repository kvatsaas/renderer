#include "Framebuffer.h"
#include "../src/png++/image.hpp"

namespace renderer {
Framebuffer::Framebuffer()
  : m_width(800), m_height(800),
    m_pixels(m_width * m_height)
{
  std::fill(m_pixels.begin(), m_pixels.end(), Vector3D(0.0f, 0.0f, 0.0f));
}

Framebuffer::Framebuffer(int w, int h)
  : m_width(w), m_height(h),
    m_pixels(m_width * m_height)
{
  std::fill(m_pixels.begin(), m_pixels.end(), Vector3D(0.0f, 0.0f, 0.0f));
}

void Framebuffer::setPixelColor(int row, int col, Vector3D rgb)
{
  m_pixels[row * m_height + col] = rgb;
}

Vector3D &Framebuffer::getPixelColor(int row, int col)
{
  return m_pixels[row * m_height + col];
}

void Framebuffer::forEachPixel(std::function<void(Vector3D &)> func)
{
  for (int i = 0; i < m_pixels.size(); i++) {
    func(m_pixels[i]);
  }
}

void Framebuffer::clearToColor(Vector3D rgb)
{
  std::function<void(Vector3D &)> func = [rgb](Vector3D &v) { v = rgb; };
  forEachPixel(func);
}

int Framebuffer::getWidth()
{
  return m_width;
}

int Framebuffer::getHeight()
{
  return m_height;
}

void Framebuffer::exportAsPNG(std::string filepath)
{
  png::image<png::rgb_pixel> image(m_width, m_height);

  for (int col = 0; col < m_height; col++) {
    for (int row = 0; row < m_width; row++) {
      Vector3D pixel = getPixelColor(row, col);
      pixel *= 255;
      pixel.bound(0, 255);
      image[m_height - 1 - col][row] = png::rgb_pixel(pixel[0], pixel[1], pixel[2]);
    }
  }

  image.write(filepath);
}

}// namespace renderer