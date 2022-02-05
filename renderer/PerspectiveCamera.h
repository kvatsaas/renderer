#pragma once 
#include "Camera.h"
#include "Ray.h"

namespace renderer {

class PerspectiveCamera : public Camera
{
public:
  void generateRay(int i, int j, Ray &ray)
  {
    float u, v;
    u = l + (r - l) * (i + 0.5) / nx;
    v = b + (t - b) * (j + 0.5) / ny;

    ray.setOrigin(position);
    Vector3D dir = -1.0 * focallength * coord.get_w() + u * coord.get_u() + v * coord.get_v();
    ray.setDirection(dir);
  }

protected:
  float l, b, r, t, nx, ny;
  float focallength;
};
}