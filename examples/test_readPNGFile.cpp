#include <iostream>
#include <cstring>

#include "png++/png.hpp"
#include "handleGraphicsArgs.h"

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  png::image< png::rgb_pixel > textureImage;

  std::cout << "Reading texture map from file: " << args.inputFileName << std::endl;
  textureImage.read( args.inputFileName );

  int imageWidth = textureImage.get_width();
  int imageHeight = textureImage.get_height();
  
  std::cout << "\timage is " << imageWidth << " X " << imageHeight << std::endl;

  png::rgb_pixel texel;
  texel = textureImage[imageHeight / 2][imageWidth / 2];

  std::cout << "Texel color at (" << imageWidth/2 << ", " << imageHeight/2 << ") = " 
	    << '[' << texel.red
	    << ", " << texel.green
	    << ", " << texel.blue << "]" << std::endl;

  exit(EXIT_SUCCESS);
}
