#pragma once
#include <string>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/string_cast.hpp>

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
   * @brief Allows the creation of a vector from a string description of one
   * @param str A string description of a vector; i.e. "1 -2 3" === Vector3D(1, -2, 3)
  */
  Vector3D(const std::string str);

  /**
	 * @brief Creates a vector from a glm::vec3
	 * @param v The vector to copy
	*/
  Vector3D(const glm::vec3 &v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  /**
	 * @brief Creates a vector from a glm::vec4
	 * @param v The vector to copy
	*/
  Vector3D(const glm::vec4 &v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }

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
	 * @brief Constrains each value in the vector to the associated values of given minimum and
            maximum vectors by truncating
	 * @param min The minimum vector
	 * @param max The maximum vector
	*/
  void bound(const Vector3D &min, const Vector3D &max);

  /**
	 * @brief Constrains each value in the vector to the associated values of a given maximum vector
            and a minimum of zero by truncating
	 * @param max The maximum vector
	*/
  void bound(const Vector3D &max);

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
    * @brief Allows use of the /= operator for scalar division
    * @param rhs The right hand side of the equation
    * @return The updated Vector3D
    */
  const Vector3D &operator/=(const float &rhs);

  /**
   * @brief Allows use of the assignment operator as a shortcut for the string constructor
   * @param str A string description of a vector; i.e. "1 -2 3" === Vector3D(1, -2, 3)
   * @return The vector described
  */
  Vector3D &operator=(const std::string str);

  /**
	 * @brief Calculates the length of the vector
	 * @return The length of the vector
	*/
  const float length() const;

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

  /**
   * @brief Returns the vector as a glm-implemented vec3
   * @return The vector as glm::vec3
  */
  glm::vec3 glmGet() const
  {
    return glm::vec3(x, y, z);
  }

  /**
   * @brief Returns the vector as a glm-implemented vec4, using the provided fourth value
   * @param w The fourth value for the vec4
   * @return The vector as glm::vec4
  */
  glm::vec4 glmGet(float w) const
  {
    return glm::vec4(x, y, z, w);
  }

  /**
   * @brief Sets this vector to be equal to the provided glm-implemented vec3
   * @param v The glm::vec3
  */
  void glmSet(const glm::vec3 &v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  /**
   * @brief Sets this vector to be equal to the provided glm-implemented vec4, truncating the fourth value
   * @param v The glm::vec4
  */
  void glmSet(const glm::vec4 &v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  /**
   * @brief Transforms the vector using the given 4x4 matrix and a fourth value for the vector.
   *        Note that the matrix is the left operand.
   * @param m The transform matrix
   * @param w The fourth value for the vector
   * @return The result as a Vector3D
  */
  Vector3D transformWithMatrix(const glm::mat4 &m, float w) const
  {
    auto temp = glmGet(w);
    auto inter = m * temp;
    auto result = Vector3D(inter);
    /*std::cout << "v: " << this->toString() << std::endl;
    std::cout << "m: " << glm::to_string(m) << std::endl;
    std::cout << "t: " << glm::to_string(temp) << std::endl;
    std::cout << "i: " << glm::to_string(inter) << std::endl;
    std::cout << "r: " << result.toString() << std::endl;*/

    return result;
  }

  /**
   * @brief Converts the vector to a string representation
   * @return A string representation of the vector
  */
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