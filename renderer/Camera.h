#pragma once
#include <string>
#include "Vector3D.h"
#include "CoordSys.h"
#include "Ray.h"

namespace renderer {

class Camera
{
public:
  virtual ~Camera() = 0;

  /**
   * @brief Creates a ray from the camera to the given pixel on the image
   * @param i The x-coordinate of the pixel
   * @param j The y-coordinate of the pixel
   * @param ray A reference to the Ray object being generated
  */
  virtual void generateRay(int i, int j, Ray &r) = 0;

  virtual std::string getName() = 0;
  virtual Vector3D &getPosition() = 0;
  virtual CoordSys &getCoord() = 0;

protected:
  std::string name;
  Vector3D position;
  CoordSys coord;
};

}// namespace renderer