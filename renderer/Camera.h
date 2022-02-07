#pragma once
#include <string>
#include "Vector3D.h"
#include "CoordSys.h"
#include "Ray.h"

namespace renderer {

class Camera
{
public:
  Camera(){}
  virtual ~Camera(){};

  /**
   * @brief Creates a ray from the camera to the given pixel on the image
   * @param i The x-coordinate of the pixel
   * @param j The y-coordinate of the pixel
   * @param ray A reference to the Ray object being generated
  */
  virtual void generateRay(int i, int j, Ray &r) = 0;

  std::string getName();
  Vector3D &getPosition();
  CoordSys &getCoord();

protected:
  std::string name;
  CoordSys coord;
  Vector3D position;
  Vector3D gaze;
};

}// namespace renderer