#include "Box.h"

namespace renderer {
Box::Box()
  : Box(Vector3D(0, 0, 0), Vector3D(1, 1, 1)) {}

Box::Box(Vector3D minPoint, Vector3D maxPoint, Shader *s)
{
  triangles = std::vector<Triangle>();
  shaderPtr = s;

  // Triangles form sides; each side description assumes max is above and in front of min.
  {
    //back
    triangles.push_back(Triangle(
      Vector3D(minPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], minPoint['z']),
      shaderPtr));

    triangles.push_back(Triangle(
      Vector3D(maxPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], minPoint['z']),
      shaderPtr));

    //front
    triangles.push_back(Triangle(
      Vector3D(minPoint['x'], minPoint['y'], maxPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], maxPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], maxPoint['z']),
      shaderPtr));

    triangles.push_back(Triangle(
      Vector3D(maxPoint['x'], maxPoint['y'], maxPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], maxPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], maxPoint['z']),
      shaderPtr));

    //bottom
    triangles.push_back(Triangle(
      Vector3D(minPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], minPoint['y'], maxPoint['z']),
      shaderPtr));

    triangles.push_back(Triangle(
      Vector3D(maxPoint['x'], minPoint['y'], maxPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], minPoint['y'], maxPoint['z']),
      shaderPtr));

    //top
    triangles.push_back(Triangle(
      Vector3D(minPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(maxPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], maxPoint['z']),
      shaderPtr));

    triangles.push_back(Triangle(
      Vector3D(maxPoint['x'], maxPoint['y'], maxPoint['z']),
      Vector3D(maxPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], maxPoint['z']),
      shaderPtr));

    //left
    triangles.push_back(Triangle(
      Vector3D(minPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], minPoint['y'], maxPoint['z']),
      shaderPtr));

    triangles.push_back(Triangle(
      Vector3D(minPoint['x'], maxPoint['y'], maxPoint['z']),
      Vector3D(minPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(minPoint['x'], minPoint['y'], maxPoint['z']),
      shaderPtr));

    //right
    triangles.push_back(Triangle(
      Vector3D(maxPoint['x'], minPoint['y'], minPoint['z']),
      Vector3D(maxPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], maxPoint['z']),
      shaderPtr));

    triangles.push_back(Triangle(
      Vector3D(maxPoint['x'], maxPoint['y'], maxPoint['z']),
      Vector3D(maxPoint['x'], maxPoint['y'], minPoint['z']),
      Vector3D(maxPoint['x'], minPoint['y'], maxPoint['z']),
      shaderPtr));
  }
}


bool Box::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit)
{
  bool hitOccurred = false;

  for (int i = 0; i < triangles.size(); i++)
    if (triangles[i].closestHit(r, tmin, tmax, hit))
      hitOccurred = true;

  return hitOccurred;
}
void Box::setShader(Shader *s)
{
  shaderPtr = s;

  for (int i = 0; i < triangles.size(); i++)
    triangles[i].setShader(shaderPtr);
}
}// namespace renderer