#include <algorithm>
#include "BVHNode.h"

namespace renderer {


BVHNode::BVHNode()
{
  bound = AABoundingBox();
}

BVHNode::BVHNode(AABoundingBox b)
{
  bound = b;
}

BVHNode::BVHNode(AABoundingBox b, Shape *left, Shape *right)
  : leftChild(left), rightChild(right)
{
  bound = b;
}

BVHNode::BVHNode(std::vector<Shape *> shapes, int axis)
{
  if (shapes.size() == 0) {
    leftChild = shapes[0];
    bound = leftChild->getBoundingBox();

  } else if (shapes.size() == 2) {
    leftChild = shapes[0];
    rightChild = shapes[1];
    bound = leftChild->getBoundingBox().merge(rightChild->getBoundingBox());

  } else {
    std::sort(shapes.begin(),
      shapes.end(),
      [axis](const Shape *lhs, const Shape *rhs) {
        auto lhsCenter = lhs->getCenter();
        auto rhsCenter = rhs->getCenter();
        return lhsCenter[axis] < rhsCenter[axis];
      });

    int mid = shapes.size() / 2;
    int nextAxis = (axis + 1) % 3;
    leftChild = new BVHNode({ shapes.begin(), shapes.begin() + mid - 1 }, nextAxis);
    rightChild = new BVHNode({ shapes.begin() + mid, shapes.end() }, nextAxis);

    bound = leftChild->getBoundingBox().merge(rightChild->getBoundingBox());
  }
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