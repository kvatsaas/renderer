#pragma once
#include "Vector3D.h"
#include "Ray.h"

namespace renderer {

class AABoundingBox
{
public:
  /**
   * @brief Constructs an axis-aligned bounding box at the point (0, 0, 0); essentially a point in space
  */
  AABoundingBox();

  /**
   * @brief Constructs an axis-aligned bounding box with the given min and max points
   * @param min The minimum point
   * @param max The maximum point
  */
  AABoundingBox(Vector3D min, Vector3D max);

  /**
   * @brief Constructs an axis-aligned bounding box at the given point; essentially a point in space
   * @param point The point
  */
  AABoundingBox(Vector3D p);

  /**
   * @brief Setter for the minimum point
   * @param min The minimum point
  */
  void setMinPoint(Vector3D min);

  /**
   * @brief Setter for the maximum point
   * @param min The maximum point
  */
  void setMaxPoint(Vector3D max);

  /**
   * @brief Getter for the minimum point
   * @return The minimum point
  */
  Vector3D &getMinPoint();

  /**
   * @brief Getter for the maximum point
   * @return The maximum point
  */
  Vector3D &getMaxPoint();

  /**
   * @brief Enlarges the bounding box to include the given point
   * @param p The point
  */
  void addPoint(Vector3D p);

  /**
   * @brief Checks if the given ray intersects the bounding box
   * @param r The ray
   * @return True if the ray intersects the bounding box
  */
  bool intersect(const Ray &r);

  /**
   * @brief Creates a new bounding box that is the union of two others
   * @param b The bounding box to merge with this one
   * @return The union of the two bounding boxes
  */
  AABoundingBox merge(const AABoundingBox &b);

private:
  Vector3D minPt, maxPt;
};
}// namespace renderer