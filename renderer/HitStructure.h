#pragma once
#include "Shader.h"
#include "Vector3D.h"
#include "Ray.h"

namespace renderer {

class HitStructure
{
public:
  HitStructure();
  HitStructure(Shader *s, Vector3D c, Ray h, Ray n, float t);

  const Shader *getShader() const;
  const Vector3D &getColor() const;
  const Ray &getHit() const;
  const Ray &getNormal() const;
  float get_t() const;

protected:
  Shader *shaderPtr;
  Vector3D color;// use in place of shader for now
  Ray hit;// ray that hit
  Ray normal;
  float t;// t value at collision point
  // Vector3D hitLocation; // maybe?
};

}