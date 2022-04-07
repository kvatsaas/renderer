#include <cmath>
#include "AABoundingBox.h"
#include <iostream>

namespace renderer {

AABoundingBox::AABoundingBox()
  : minPt(), maxPt() {}

AABoundingBox::AABoundingBox(Vector3D min, Vector3D max)
  : minPt(min), maxPt(max) {}

AABoundingBox::AABoundingBox(Vector3D p)
  : minPt(p), maxPt(p) {}

void AABoundingBox::setMinPoint(Vector3D min)
{
  minPt = min;
}

void AABoundingBox::setMaxPoint(Vector3D max)
{
  maxPt = max;
}

Vector3D &AABoundingBox::getMinPoint()
{
  return minPt;
}

Vector3D &AABoundingBox::getMaxPoint()
{
  return maxPt;
}

void AABoundingBox::setVisibleDepthBounds(int min, int max)
{
  minDepthVisible = min;
  maxDepthVisible = max;
}

void AABoundingBox::setShadowDepthBounds(int min, int max)
{
  minDepthShadow = min;
  maxDepthShadow = max;
}

void AABoundingBox::addPoint(Vector3D p)
{
  if (p['x'] < minPt['x'])
    minPt['x'] = p['x'];
  else if (p['x'] > maxPt['x'])
    maxPt['x'] = p['x'];

  if (p['y'] < minPt['y'])
    minPt['y'] = p['y'];
  else if (p['y'] > maxPt['y'])
    maxPt['y'] = p['y'];

  if (p['z'] < minPt['z'])
    minPt['z'] = p['z'];
  else if (p['z'] > maxPt['z'])
    maxPt['z'] = p['z'];
}

bool AABoundingBox::intersect(const Ray &r, int depth)
{
  auto origin = r.getOrigin();
  auto direction = r.getDirection();
  float txmin, txmax, tymin, tymax, tzmin, tzmax;

  if (direction['x'] >= 0) {
    txmin = (minPt['x'] - origin['x']) * (1 / direction['x']);
    txmax = (maxPt['x'] - origin['x']) * (1 / direction['x']);
  } else {
    txmin = (maxPt['x'] - origin['x']) * (1 / direction['x']);
    txmax = (minPt['x'] - origin['x']) * (1 / direction['x']);
  }

  if (direction['y'] >= 0) {
    tymin = (minPt['y'] - origin['y']) * (1 / direction['y']);
    tymax = (maxPt['y'] - origin['y']) * (1 / direction['y']);
  } else {
    tymin = (maxPt['y'] - origin['y']) * (1 / direction['y']);
    tymax = (minPt['y'] - origin['y']) * (1 / direction['y']);
  }

  if (txmin > tymax || txmax < tymin)
    return false;

  if (direction['z'] >= 0) {
    tzmin = (minPt['z'] - origin['z']) * (1 / direction['z']);
    tzmax = (maxPt['z'] - origin['z']) * (1 / direction['z']);
  } else {
    tzmin = (maxPt['z'] - origin['z']) * (1 / direction['z']);
    tzmax = (minPt['z'] - origin['z']) * (1 / direction['z']);
  }

  if (std::max(txmin, tymin) > tzmax || std::min(txmax, tymax) < tzmin)
    return false;
  else
    return true;
}

bool AABoundingBox::intersectClosest(const Ray &r, int depth)
{
  if (depth < minDepthVisible || depth > maxDepthVisible)
    return false;
  else
    return intersect(r, depth);
}

bool AABoundingBox::intersectAny(const Ray &r, int depth)
{
  if (depth < minDepthShadow || depth > maxDepthShadow)
    return false;
  else
    return intersect(r, depth);
}

AABoundingBox AABoundingBox::merge(const AABoundingBox &b) const
{
  float xmin, xmax, ymin, ymax, zmin, zmax;
  AABoundingBox bound;

  xmin = std::min(this->minPt['x'], b.minPt['x']);
  ymin = std::min(this->minPt['y'], b.minPt['y']);
  zmin = std::min(this->minPt['z'], b.minPt['z']);

  xmax = std::max(this->maxPt['x'], b.maxPt['x']);
  ymax = std::max(this->maxPt['y'], b.maxPt['y']);
  zmax = std::max(this->maxPt['z'], b.maxPt['z']);

  bound = AABoundingBox(
    Vector3D(xmin, ymin, zmin),
    Vector3D(xmax, ymax, zmax));
  bound.setVisibleDepthBounds(std::min(this->minDepthVisible, b.minDepthVisible), std::max(this->maxDepthVisible, b.maxDepthVisible));
  bound.setShadowDepthBounds(std::min(this->minDepthShadow, b.minDepthShadow), std::max(this->maxDepthShadow, b.maxDepthShadow));
  return bound;
}

}// namespace renderer