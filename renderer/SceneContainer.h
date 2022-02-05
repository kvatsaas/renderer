#pragma once
#include <map>
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Shader.h"
#include "Shape.h"

namespace renderer {

class SceneContainer
{
public:
  SceneContainer();

  void addCamera(Camera &c);
  void addLight(Light &l);
  void addShader(Shader &s);
  void addShape(Shape &s);

protected:
  std::vector<Camera *> cameras;
  std::vector<Light *> lights;
  std::map<std::string, Shader *> shaders;
  std::vector<Shape *> shapes;
};

}// namespace renderer
