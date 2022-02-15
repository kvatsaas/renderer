#include "Vector3D.h"
#include <iostream>

using namespace renderer;

// tests access via [] operator
void printVector3D(std::string name, const Vector3D &v)
{
	std::cout << name << ": (" << v['x'] << ", " << v['y'] << ", " << v['z'] << ')' << std::endl;
}

void testVector3D() {
  // test basic constructor
  Vector3D a(1, 2, 3);
  printVector3D("a", a);
  std::cout << std::endl;

  // test default constructor
  Vector3D b;
  printVector3D("b", b);
  std::cout << std::endl;

  // test modification via [] operator
  b['x'] = 5;
  b['y'] = 10;
  b['z'] = 15;
  printVector3D("b", b);
  std::cout << std::endl;

  // test copy constructor and == operator
  Vector3D c(b);
  printVector3D("c", c);
  std::cout << "c == b should be true: " << (c == b) << std::endl;
  std::cout << "c == a should be false: " << (c == a) << std::endl;
  std::cout << std::endl;

  // test scaling; *, *= for float
  printVector3D("a.scale(3)", a.scale(3));
  printVector3D("a * 3", a * 3);
  printVector3D("3 * a", 3 * a);
  Vector3D d = a;
  a *= 3;
  printVector3D("a *= 3", a);
  std::cout << std::endl;

  // test = operator
  printVector3D("d", d);
  std::cout << "a == d should be false: " << (a == d) << std::endl;
  a = d;
  printVector3D("a", a);
  std::cout << "a == d should be true: " << (a == d) << std::endl;
  std::cout << std::endl;

  // test +, -, +=, -=
  printVector3D("a", a);
  printVector3D("b", b);
  printVector3D("a + b", a + b);
  printVector3D("b - a", b - a);
  a += b;
  printVector3D("a += b", a);
  a -= b;
  printVector3D("a restored", a);
  b -= a;
  printVector3D("b -= a", b);
  b += a;
  printVector3D("b restored", b);
  std::cout << std::endl;

  // test *, *= for Vector3D; /, /=
  Vector3D e(10, 40, 90);
  printVector3D("e", e);
  printVector3D("a * e", a * e);
  printVector3D("e / a", e / a);
  a *= e;
  printVector3D("a *= e", a);
  a /= e;
  printVector3D("a restored", a);
  e /= a;
  printVector3D("e /= a", e);
  e *= a;
  printVector3D("e restored", e);
  std::cout << std::endl;

  // test length
  printVector3D("a", a);
  std::cout << "length of a: " << a.length() << std::endl;
  printVector3D("b", b);
  std::cout << "length of b: " << b.length() << std::endl;
  printVector3D("c", c);
  std::cout << "length of c: " << c.length() << std::endl;
  printVector3D("d", d);
  std::cout << "length of d: " << d.length() << std::endl;
  printVector3D("e", e);
  std::cout << "length of e: " << e.length() << std::endl;
  std::cout << std::endl;

  // test dot product
  std::cout << "a . b: " << a.dotProduct(b) << std::endl;
  std::cout << "b . a: " << b.dotProduct(a) << std::endl;
  std::cout << "a . a: " << a.dotProduct(a) << std::endl;
  std::cout << "a . e: " << a.dotProduct(e) << std::endl;
  std::cout << "b . b: " << b.dotProduct(b) << std::endl;
  std::cout << "b . e: " << b.dotProduct(e) << std::endl;
  std::cout << std::endl;

  // test unit vector
  printVector3D("a", a);
  printVector3D("unit vector of a: ", a.unitVector());
  printVector3D("d", d);
  printVector3D("unit vector of d: ", d.unitVector());
  printVector3D("e", e);
  printVector3D("unit vector of e: ", e.unitVector());
  std::cout << std::endl;

  // test bound
  Vector3D f(-5, -2, -500);
  Vector3D g(256, 260, 500);
  Vector3D h(0, 20, 255);
  printVector3D("f", f);
  f.bound(0, 255);
  printVector3D("f bound to 0-255", f);
  printVector3D("g", g);
  g.bound(0, 255);
  printVector3D("g bound to 0-255", g);
  printVector3D("h", h);
  h.bound(0, 255);
  printVector3D("h bound to 0-255", h);
  std::cout << std::endl;

  // prescribed test
  b = Vector3D(4, 4, -1);
  printVector3D("a", a);
  printVector3D("b", b);
  std::cout << "a . b: " << a.dotProduct(b) << std::endl;
}

int main() {
  testVector3D();
}