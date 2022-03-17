#include "BVHNode.h"

namespace renderer {


BVHNode::BVHNode()
  : leftChild(nullptr), rightChild(nullptr)
{
  bound = AABoundingBox();
}

BVHNode::BVHNode(AABoundingBox b)
  : leftChild(nullptr), rightChild(nullptr)
{
  bound = b;
}

BVHNode::BVHNode(AABoundingBox b, Shape *left, Shape *right)
  : leftChild(left), rightChild(right)
{
  bound = b;
}

void BVHNode::setLeftChild(Shape *s)
{
  leftChild = s;
}

void BVHNode::setRightChild(Shape *s)
{
  rightChild = s;
}

Shape *BVHNode::getLeftChild()
{
  return leftChild;
}

Shape *BVHNode::getRightChild()
{
  return rightChild;
}

bool BVHNode::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit)
{
  if (!bound.intersect(r))
    return false;

  bool leftHit = false, rightHit = false;
  auto local_tmax = tmax;
  auto leftHitStruct = HitStructure();
  auto rightHitStruct = HitStructure();
  if (leftChild)
    leftHit = leftChild->closestHit(r, tmin, local_tmax, leftHitStruct);
  if (rightChild)
    rightHit = rightChild->closestHit(r, tmin, local_tmax, rightHitStruct);

  if (leftHit) {
    if (rightHit && rightHitStruct.get_t() < leftHitStruct.get_t()) {//if both hit
      hit = rightHitStruct;
      tmax = rightHitStruct.get_t();
    } else {
      hit = leftHitStruct;
      tmax = leftHitStruct.get_t();
    }
    return true;
  } else if (rightHit) {
    hit = rightHitStruct;
    tmax = rightHitStruct.get_t();
    return true;
  }

  return false;
}

bool BVHNode::hit(const Ray &r, float tmin, float tmax)
{
  if (!bound.intersect(r))
    return false;

  return ((leftChild) && leftChild->hit(r, tmin, tmax)) || ((rightChild) && rightChild->hit(r, tmin, tmax));
}

}// namespace renderer