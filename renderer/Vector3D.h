#ifndef _VECTOR_3D
#define _VECTOR_3D

namespace renderer {

class Vector3D
{
public:
	// default constructor
	Vector3D();

	// basic constructor
	Vector3D(float a, float b, float c);

	// copy constructor
	Vector3D(const Vector3D &v);

	// scale vector by scalar value
	Vector3D scale(const float scalar) const;

	// constrain to min and max bounds
	void bound(const float min, const float max);

	// access with []
	const float operator[](const int index) const;

	// change values with []
	float &operator[](const int index);

	// override = operator
	const Vector3D &operator=(const Vector3D &rhs);

    // override += operator to add two vectors
    const Vector3D &operator+=(const Vector3D &rhs);

    // override -= operator to subtract one vector from another
    const Vector3D &operator-=(const Vector3D &rhs);

    // override *= operator to multiply two vectors, value-wise
    const Vector3D &operator*=(const Vector3D &rhs);

    // override /= operator to divide one vector by another, value-wise
    const Vector3D &operator/=(const Vector3D &rhs);

	// override *= operator for scaling
	const Vector3D &operator*=(const float &rhs);

	// calculate length of a vector
	float length() const;

	// calculate dot product of two vectors
	const float dotProduct(const Vector3D &rhs) const;

	// create unit vector of this vector
	Vector3D unitVector() const;

private:
	float x;
	float y;
	float z;
};

// override + operator to add two vectors
const Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs);

// override - operator to subtract one vector from another
const Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs);

// override * operator to scale vector, allowing for interchangeable positioning
const Vector3D operator*(const float lhs, const Vector3D &rhs);
const Vector3D operator*(const Vector3D &lhs, const float rhs);

// override * operator to multiply two vectors, value-wise
const Vector3D operator*(const Vector3D &lhs, const Vector3D &rhs);

// override / operator to divide one vector by another, value-wise
const Vector3D operator/(const Vector3D &lhs, const Vector3D &rhs);

// test equality of two vectors
bool operator==(const Vector3D &lhs, const Vector3D &rhs);

}


#endif