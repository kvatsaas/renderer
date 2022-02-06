#pragma once 
#include "Camera.h"
#include "Ray.h"

namespace renderer {

class PerspectiveCamera : public Camera
{
public:
  /**
   * @brief Creates a default camera with a 20x20 image plane and image size, and a focal length of 0.5
  */
  PerspectiveCamera();

  /**
   * @brief Creates a perspective camera with the given specifications.
   * @param camName The name of the camera
   * @param pos The position of the camera within the scene
   * @param cs The coordinate system being used
   * @param fl The focal length of the camera
   * @param width The width of the image plane
   * @param height The height of the image plane
   * @param n_x The pixel width of the output
   * @param n_y The pixel height of the output
  */
  PerspectiveCamera(std::string camName, Vector3D pos, CoordSys cs, float fl, float width, float height, float n_x, float n_y);
  
  /**
   * @brief Creates a ray from the camera to the given pixel on the image
   * @param i The x-coordinate of the pixel
   * @param j The y-coordinate of the pixel
   * @param ray A reference to the Ray object being generated
  */
  void generateRay(int i, int j, Ray &ray)
  {
    float u, v;
    u = l + (r - l) * (i + 0.5) / nx;
    v = b + (t - b) * (j + 0.5) / ny;

    Vector3D direction = -1.0 * focalLength * coord.get_w() + u * coord.get_u() + v * coord.get_v();

    ray = Ray(position, direction);
  }

protected:
  float l, b, r, t, nx, ny;
  float focalLength;
};
}