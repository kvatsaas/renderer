#pragma once
#include "Vector3D.h"

namespace renderer {

class Ray
{
public:
  /**
   * @brief Creates a default Ray at (0, 0, 0) with a direction of (1, 1, 1)
  */
  Ray()
    : origin(0, 0, 0), direction(1, 1, 1) {}

  /**
   * @brief Creates a Ray with the given attributes
   * @param o The origin of the Ray
   * @param d The direction of the Ray
  */
  Ray(Vector3D &o, Vector3D &d)
    : origin(o), direction(d) {}

  /**
   * @brief Getter for the Ray's origin
   * @return A reference to the origin of the Ray
  */
  const Vector3D &getOrigin() const;

  /**
   * @brief Getter for the Ray's direction
   * @return A reference to the direction of the Ray
  */
  const Vector3D &getDirection() const;

  /**
   * @brief Setter for the Ray's origin
   * @param o A reference to the new origin for the Ray
  */
  void setOrigin(Vector3D &o);

  /**
   * @brief Setter for the Ray's direction
   * @param o A reference to the new direction for the Ray
  */
  void setDirection(Vector3D &d);

protected:
  Vector3D origin, direction;
};

};