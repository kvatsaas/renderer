#ifndef _FRAMEBUFFER
#define _FRAMEBUFFER

#include <vector>
#include "Vector3D.h"
#include <string>
#include <functional>

namespace renderer {

class Framebuffer
{

public:
  /** \brief Default constructor
  * 
  * Creates an 800x800 framebuffer and fills it with black pixels (#000000).
  */
  Framebuffer();

  /** \brief Parameterized constructor
  * 
  * Creates framebuffer with the given dimensions and fills it with black pixels (#000000).
  * 
  * @param w - the width of the framebuffer in pixels
  * @param h - the height of the framebuffer in pixels
  */
  Framebuffer(int w, int h);

  /** \brief Parameterized constructor
  * 
  * Creates framebuffer with the given dimensions and fills it with the given color.
  * 
  * @param w - the width of the framebuffer in pixels
  * @param h - the height of the framebuffer in pixels
  * @param color - The fill color
  */
  Framebuffer(int w, int h, Vector3D color);

  /** \brief Set the color of a pixel
  * 
  * Sets the pixel at the given location to a given RGB value (as a Vector3D).
  * 
  * @param row - the row of the pixel
  * @param col - the column of the pixel
  * @param rgb - the rgb value to set the pixel to
  */
  void setPixelColor(int row, int col, Vector3D rgb);

  /** \brief Get the color of a pixel
  * 
  * Returns the RGB value (as a Vector3D) of a given pixel.
  * 
  * @param row - the row of the pixel
  * @param col - the column of the pixel
  * @return the rgb value of the pixel
  */
  Vector3D &getPixelColor(int row, int col);

  /** \brief Apply a function to every pixel
  * 
  * Given a lambda function that modifies a Vector3D object in some way, applies that function
  * to each pixel in the framebuffer.
  * 
  * @param func - a lambda function that takes a reference to a Vector3D and modifies it in some way
  */
  void forEachPixel(std::function<void(Vector3D &)> func);

  /** \brief Set all pixels to a color
  * 
  * Sets every pixel in the framebuffer to the given RGB value (as a Vector3D).
  * 
  * @param rgb - the RGB value to set all the pixels to
  */
  void clearToColor(Vector3D rgb);

  /** \brief Returns the width
  * 
  * Returns the width, in pixels, of the framebuffer.
  * 
  * @return the width of the framebuffer in pixels
  */
  int getWidth();

  /** \brief Returns the height
  * 
  * Returns the height, in pixels, of the framebuffer.
  * 
  * @return the height of the framebuffer in pixels
  */
  int getHeight();

  /** \brief Export to a PNG file
  * 
  * Writes the framebuffer to a PNG file at the path given.
  * 
  * @param filepath - the path to write the PNG to
  */
  void exportAsPNG(std::string filepath);

private:
  int m_width;
  int m_height;
  std::vector<Vector3D> m_pixels;
};

}// namespace renderer

#endif