#pragma once
#include <string>
#include <vector>
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
  virtual void generateRay(int i, int j, Ray &ray) = 0;

  /**
   * @brief Creates a stratified sample of rays for the given pixel on the image
   * @param i The x-coordinate of the pixel
   * @param j The y-coordinate of the pixel
   * @param n An integer that represents the dimension of the sample grid
   * @param ray A reference to a vector to store the generated rays
  */
  virtual void generateSampleRays(int i, int j, int n, std::vector<Ray> &rays) = 0;

  /**
   * @brief Getter for the camera name
   * @return The name of the camera
  */
  std::string getName();

  /**
   * @brief Getter for the camera position
   * @return The position of the camera
  */
  Vector3D &getPosition();

  /**
   * @brief Getter for the coordinate system of the camera
   * @return The coordinate system of the camera
  */
  CoordSys &getCoord();

protected:
  std::string name;
  CoordSys coord;
  Vector3D position;
};

}// namespace renderer