#pragma once
#include <vector>
#include "Shape.h"
#include "AABoundingBox.h"

namespace renderer {

class BVHNode : public Shape
{
public:

  /**
   * @brief Creates a BVHNode with a default bounding box and no children
  */
  BVHNode();

  /**
   * @brief Creates a BVHNode with the given bounding box and no children
   * @param b The bounding box
  */
  BVHNode(AABoundingBox b);

  /**
   * @brief Creates a BVHNode with the given bounding box and the given children
   * @param b The bounding box
   * @param left The left child
   * @param right The right child
  */
  BVHNode(AABoundingBox b, Shape *left, Shape *right);

  /**
   * @brief Creates a BVH tree for the given shapes with this node as the root
   * @param shapes A vector of pointers to the shapes in the scene
   * @param axis The current axis (0 = x, 1 = y, 2 = z) on which to sort. Defaults to 0 (x).
  */
  BVHNode(std::vector<Shape *> shapes, int axis = 0);

  /**
   * @brief Setter for the left child
   * @param s The left child
  */
  void setLeftChild(Shape *s);

  /**
   * @brief Setter for the right child
   * @param s The right child
  */
  void setRightChild(Shape *s);

  /**
   * @brief Getter for the left child
   * @return s The left child
  */
  Shape *getLeftChild();

  /**
   * @brief Getter for the right child
   * @return s The right child
  */
  Shape *getRightChild();

  /**
   * @brief Getter for number of children, grandchildren, etc
   * @return The number of children
  */
  int getChildren();

  /**
   * @brief Getter for the number of leaves that are somewhere under this node
   * @return The number of leaves
  */
  int getLeaves();

  /**
   * @brief Determines whether the given ray intersects with the box at this node and modifies
   *        the given hit structure if it does
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @param hit A HitStructure that will be filled in the event of a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth);

  /**
   * @brief Determines whether the given ray intersects with this node
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool hit(const Ray &r, float tmin, float tmax, int depth);

protected:
  Shape *leftChild = nullptr;
  Shape *rightChild = nullptr;
  int children;
  int leaves;
};

}// namespace renderer