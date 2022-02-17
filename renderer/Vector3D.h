#include <string>
#ifndef _VECTOR_3D
#define _VECTOR_3D

namespace renderer {

class Vector3D
{
public:
  /**
	 * @brief Creates a default vector - (0, 0, 0)
	*/
  Vector3D();

  /**
	 * @brief Creates a vector with the given values
	 * @param a The first value of the vector (x)
	 * @param b The second value of the vector (y)
	 * @param c The third value of the vector (z)
	*/
  Vector3D(float a, float b, float c);

  /**
	 * @brief Creates a vector identical to another
	 * @param v The vector to copy
	*/
  Vector3D(const Vector3D &v);

  /**
	 * @brief Creates a new vector equal to this vector with each value multiplied by a given scalar
	 * @param scalar The value to scale by
	 * @return The scaled vector
	*/
  Vector3D scale(const float scalar) const;

  /**
	 * @brief Constrains each value in the vector to a given minimum and maximum by truncating
	 * @param min The minimum value
	 * @param max The maximum value
	*/
  void bound(const float min, const float max);

  /**
	 * @brief Allows access to the vector with the [] operator using an int as index
	 * @param index The index of the value (0 for x, 1 for y, 2 for z)
	 * @return The requested value
	*/
  const float operator[](const int index) const;

  /**
	 * @brief Allows modification the vector with the [] operator using an int as index
	 * @param index The index of the value (0 for x, 1 for y, 2 for z)
	 * @return A reference to the requested value
	*/
  float &operator[](const int index);

  /**
	 * @brief Allows access to the vector with the [] operator using a char as index
	 * @param index The index of the value (x, y, z)
	 * @return The requested value
	*/
  const float operator[](const char index) const;

  /**
	 * @brief Allows modification the vector with the [] operator using a char as index
	 * @param index The index of the value (x, y, z)
	 * @return A reference to the requested value
	*/
  float &operator[](const char index);

  /**
	 * @brief Allows use of the assignment operator
	 * @param rhs The new value for this Vector3D
	 * @return The updated Vector3D
	*/
  const Vector3D &operator=(const Vector3D &rhs);

  /**
    * @brief Allows use of the += operator
    * @param rhs The right hand side of the equation
    * @return The updated Vector3D
    */
  const Vector3D &operator+=(const Vector3D &rhs);

  /**
    * @brief Allows use of the -= operator
    * @param rhs The right hand side of the equation
    * @return The updated Vector3D
    */
  const Vector3D &operator-=(const Vector3D &rhs);

  /**
    * @brief Allows use of the *= operator for value-wise multiplication
    * @param rhs The right hand side of the equation
    * @return The updated Vector3D
    */
  const Vector3D &operator*=(const Vector3D &rhs);

  /**
    * @brief Allows use of the /= operator for value-wise division
    * @param rhs The right hand side of the equation
    * @return The updated Vector3D
    */
  const Vector3D &operator/=(const Vector3D &rhs);

  /**
    * @brief Allows use of the *= operator for scaling
    * @param rhs The right hand side of the equation
    * @return The updated Vector3D
    */
  const Vector3D &operator*=(const float &rhs);

  /**
	 * @brief Calculates the length of the vector
	 * @return The length of the vector
	*/
  float length() const;

  /**
	 * @brief Calculates the dot product of this vector and another
	 * @param rhs The other vector
	 * @return The dot product
	*/
  const float dotProduct(const Vector3D &rhs) const;

  /**
	 * @brief Calculates the cross product of this vector and another
	 * @param rhs The other vector
	 * @return The dot product
	*/
  const Vector3D crossProduct(const Vector3D &rhs) const;

  /**
	 * @brief Creates a unit vector in the direction of this vector
	 * @return The unit vector
	*/
  Vector3D normalize() const;

  std::string toString() const;

private:
  float x;
  float y;
  float z;
};

/**
 * @brief Overrides the addition operator for value-wise addition
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return The resulting vector
*/
const Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs);

/**
 * @brief Overrides the subtraction operator for value-wise subtraction
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return The resulting vector
*/
const Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs);

/**
 * @brief Overrides the multiplication operator for scaling with the vector in the right position
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return The resulting vector
*/
const Vector3D operator*(const float lhs, const Vector3D &rhs);

/**
 * @brief Overrides the multiplication operator for scaling with the vector in the left position
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return The resulting vector
*/
const Vector3D operator*(const Vector3D &lhs, const float rhs);

/**
 * @brief Overrides the multiplication operator for value-wise multiplication
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return The resulting vector
*/
const Vector3D operator*(const Vector3D &lhs, const Vector3D &rhs);

/**
 * @brief Overrides the division operator for value-wise division by a constant (inverse scaling)
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return The resulting vector
*/
const Vector3D operator/(const Vector3D &lhs, const float rhs);

/**
 * @brief Overrides the division operator for value-wise division
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return The resulting vector
*/
const Vector3D operator/(const Vector3D &lhs, const Vector3D &rhs);

/**
 * @brief Overrides the equality operator
 * @param lhs The left hand side of the equation
 * @param rhs The right hand side of the equation
 * @return True if the vectors are equal, otherwise false
*/
bool operator==(const Vector3D &lhs, const Vector3D &rhs);

}// namespace renderer


#endif