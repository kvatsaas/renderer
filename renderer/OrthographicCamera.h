#pragma once 
#include "Camera.h"

namespace renderer {

class OrthographicCamera : public Camera
{
public:
  OrthographicCamera();
  OrthographicCamera(std::string camName, Vector3D pos, CoordSys cs, float left, float right, float bottom, float top, float n_x, float n_y);
  void generateRay(int i, int j, Ray &ray)
  {
    float u, v;
    u = l + (r - l) * (i + 0.5) / nx;
    v = b + (t - b) * (j + 0.5) / ny;

    ray.setOrigin(Vector3D(u, v, 0)); // fix
    Vector3D dir = coord.get_w() * -1.0;
    ray.setDirection(dir);
  }

protected:
  float l, r, b, t, nx, ny;
  float focallength;
};

}// namespace renderer