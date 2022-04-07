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
  if (shapes.size() == 1) {
    leftChild = shapes[0];
    bound = leftChild->getBoundingBox();
    children = 1;
    leaves = 1;

  } else if (shapes.size() == 2) {
    leftChild = shapes[0];
    rightChild = shapes[1];
    bound = leftChild->getBoundingBox().merge(rightChild->getBoundingBox());
    children = 2;
    leaves = 2;

  } else {
    std::sort(shapes.begin(),
      shapes.end(),
      [axis](const Shape *lhs, const Shape *rhs) {
        auto lhsCenter = lhs->getCenter();
        auto rhsCenter = rhs->getCenter();
        return lhsCenter[axis] < rhsCenter[axis];
      });

    int nextAxis = (axis + 1) % 3;
    int mid = shapes.size() / 2;
    std::vector<Shape *> leftVec = { shapes.begin(), shapes.begin() + mid };
    std::vector<Shape *> rightVec = { shapes.begin() + mid, shapes.end() };
    leftChild = new BVHNode(leftVec, nextAxis);
    rightChild = new BVHNode(rightVec, nextAxis);

    bound = leftChild->getBoundingBox().merge(rightChild->getBoundingBox());
    children = ((BVHNode *)leftChild)->getChildren() + ((BVHNode *)rightChild)->getChildren() + 2;
    leaves = ((BVHNode *)leftChild)->getLeaves() + ((BVHNode *)rightChild)->getLeaves();
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

int BVHNode::getChildren()
{
  return children;
}

int BVHNode::getLeaves()
{
  return leaves;
}

bool BVHNode::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth)
{
  if (!bound.intersect(r, depth, true))
    return false;

  bool leftHit = false, rightHit = false;
  auto local_tmax = tmax;
  auto leftHitStruct = HitStructure();
  auto rightHitStruct = HitStructure();
  if (leftChild)
    leftHit = leftChild->closestHit(r, tmin, local_tmax, leftHitStruct, depth);
  if (rightChild)
    rightHit = rightChild->closestHit(r, tmin, local_tmax, rightHitStruct, depth);

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

bool BVHNode::hit(const Ray &r, float tmin, float tmax, int depth)
{
  if (!bound.intersect(r, depth, false))
    return false;

  return ((leftChild) && leftChild->hit(r, tmin, tmax, depth)) || ((rightChild) && rightChild->hit(r, tmin, tmax, depth));
}

}// namespace renderer