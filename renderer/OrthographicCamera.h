#pragma once 
#include "Camera.h"

namespace renderer {

class OrthographicCamera : public Camera
{
public:
  /**
   * @brief Creates a default camera with a 0.5x0.5 image plane and 20x20 image size
  */
  OrthographicCamera();

  /**
   * @brief Creates a perspective camera with the given specifications.
   * @param camName The name of the camera
   * @param pos The position of the camera within the scene
   * @param cs The coordinate system being used
   * @param width The width of the image plane
   * @param height The height of the image plane
   * @param n_x The pixel width of the output
   * @param n_y The pixel height of the output
  */
  OrthographicCamera(std::string camName, Vector3D pos, CoordSys cs, float width, float height, float n_x, float n_y);
  
  /**
   * @brief Creates a ray from the camera to the given pixel on the image
   * @param i The x-coordinate of the pixel
   * @param j The y-coordinate of the pixel
   * @param ray A reference to the Ray object being generated
  */
  void generateRay(int i, int j, Ray &ray)
  {
    float u, v, w;
    u = l + (r - l) * (i + 0.5) / nx;
    v = b + (t - b) * (j + 0.5) / ny;

    Vector3D origin = position + (u * coord.get_u()) + (v * coord.get_w());
    Vector3D direction = coord.get_w() * -1.0;

    ray = Ray(origin, direction);
  }

protected:
  float l, r, b, t, nx, ny;
};

}// namespace renderer