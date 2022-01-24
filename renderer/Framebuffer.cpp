#include "Framebuffer.h"

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
  int index = row * m_height + col;
  m_pixels[index] = rgb;
}

Vector3D &Framebuffer::getPixelColor(int row, int col)
{
  int index = row * m_height + col;
  return m_pixels[index];
}

int Framebuffer::getWidth()
{
  return m_width;
}

int Framebuffer::getHeight()
{
  return m_height;
}

}// namespace renderer