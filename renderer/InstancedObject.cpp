#include "InstancedObject.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace renderer {

InstancedObject::InstancedObject(Shape *&rShape, glm::mat4 &m, glm::mat4 &inverse)
{
  refShape = rShape;
  mInv = inverse;
  mTransposeInv = glm::transpose(mInv);
  //std::cout << "m: " <<  glm::to_string(m) << std::endl;
  //std::cout << "minv: " << glm::to_string(mInv) << std::endl;
  //std::cout << "mTransposeInv: " <<  glm::to_string(mTransposeInv) << std::endl;

  /*
  * DEAL
  *     WITH
  *         BOUNDING
  *                 BOX
  */
  // in an effort to make this more readable...
  auto bmin_x = refShape->getBoundingBox().getMinPoint()['x'];
  auto bmin_y = refShape->getBoundingBox().getMinPoint()['y'];
  auto bmin_z = refShape->getBoundingBox().getMinPoint()['z'];
  auto bmax_x = refShape->getBoundingBox().getMaxPoint()['x'];
  auto bmax_y = refShape->getBoundingBox().getMaxPoint()['y'];
  auto bmax_z = refShape->getBoundingBox().getMaxPoint()['z'];

  std::vector<Vector3D> transformBound;
  transformBound.push_back(Vector3D(bmax_x, bmax_y, bmax_z).transformWithMatrix(m, 1.0f));
  transformBound.push_back(Vector3D(bmin_x, bmin_y, bmax_z).transformWithMatrix(m, 1.0f));
  transformBound.push_back(Vector3D(bmax_x, bmin_y, bmax_z).transformWithMatrix(m, 1.0f));
  transformBound.push_back(Vector3D(bmin_x, bmax_y, bmax_z).transformWithMatrix(m, 1.0f));
  transformBound.push_back(Vector3D(bmin_x, bmin_y, bmin_z).transformWithMatrix(m, 1.0f));
  transformBound.push_back(Vector3D(bmax_x, bmin_y, bmin_z).transformWithMatrix(m, 1.0f));
  transformBound.push_back(Vector3D(bmax_x, bmax_y, bmin_z).transformWithMatrix(m, 1.0f));
  transformBound.push_back(Vector3D(bmin_x, bmax_y, bmin_z).transformWithMatrix(m, 1.0f));

  for (int i = 0; i < transformBound.size(); i++)
    bound.addPoint(transformBound[i]);
}

bool InstancedObject::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth)
{
  Ray inverse = Ray(r.getOrigin().transformWithMatrix(mInv, 1.0f), r.getDirection().transformWithMatrix(mInv, 0.0f));

  if (refShape->closestHit(inverse, tmin, tmax, hit, depth)) {
    hit.setHit(r);

    Vector3D hitPt = r.getOrigin() + r.getDirection() * hit.get_t();
    Vector3D normalDir = hit.getNormal().getDirection().transformWithMatrix(mTransposeInv, 0.0).normalize();
    hit.setNormal(Ray(hitPt, normalDir));

    hit.setShape(this);
    if (shaderPtr)
      hit.setShader(shaderPtr);
    else
      hit.setShader(refShape->getShader());

    return true;
  } else {
    return false;
  }
}

bool InstancedObject::hit(const Ray &r, float tmin, float tmax, int depth)
{
  Ray inverse = Ray(r.getOrigin().transformWithMatrix(mInv, 1.0f), r.getDirection().transformWithMatrix(mInv, 0.0f));

  if (refShape->hit(inverse, tmin, tmax, depth)) {
    return true;
  } else {
    return false;
  }
}
}// namespace renderer