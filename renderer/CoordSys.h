#pragma once
#include "Vector3D.h"

namespace renderer {

// Coordinate Sys - represent arbitrary 3D bases
// -- could be called OrthonormalBasis
// -- ortho -- means at 90 degrees to each other
// -- normal -- unit length

class CoordSys
{
public:
  /**
   * @brief Creates the default coordinate system, aligned with the xyz coordinates
  */
  CoordSys();

  /**
   * @brief Creates a coordinate system using the given uvw axes
   * @param u The u axis
   * @param v The v axis
   * @param w The w axis
  */
  CoordSys(const Vector3D &u, const Vector3D &v, const Vector3D &w);

  /**
   * @brief Creates a coordinate system for a given gaze direction.
   * @param gazeDirection The gaze direction on which to base the coordinate system
   * @param tempUp A temporary value to be used as up for the purposes of calculations.
  */
  CoordSys(const Vector3D &gazeDirection, Vector3D tempUp = Vector3D(0, 1, 0));

  /**
   * @brief Returns the vector of the u axis
   * @return The vector of the u axis
  */
  const Vector3D &get_u() const;

  /**
   * @brief Returns the vector of the v axis
   * @return The vector of the u axis
  */
  const Vector3D &get_v() const;

  /**
   * @brief Returns the vector of the w axis
   * @return The vector of the u axis
  */
  const Vector3D &get_w() const;

protected:
  // Need to represent each vector of the basis
  Vector3D u, v, w;
};

}// namespace renderer