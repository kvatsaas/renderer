#include "SceneContainer.h"

namespace renderer {
SceneContainer::SceneContainer()
  : cameras(), shaders(), shapes(), bgColor() {}

void SceneContainer::addCamera(Camera *c)
{
  cameras.push_back(c);
}

void SceneContainer::addLight(Light *l)
{
  lights.push_back(l);
}

void SceneContainer::addShader(Shader *s)
{
  shaders.insert({ s->getName(), s });
}

void SceneContainer::addShape(Shape *s)
{
  shapes.push_back(s);
}

void SceneContainer::setBGColor(Vector3D bg)
{
  bgColor = bg;
}

const std::vector<Camera *> &SceneContainer::getCameras()
{
  return cameras;
}

const std::vector<Light *> &SceneContainer::getLights()
{
  return lights;
}

const Shader *SceneContainer::getShader(std::string name)
{
  if (shaders.count(name))
    return shaders[name];
  else
    return nullptr;
}

const std::map<std::string, Shader *> &SceneContainer::getShaders()
{
  return shaders;
}

const std::vector<Shape *> &SceneContainer::getShapes()
{
  return shapes;
}

const Vector3D &SceneContainer::getBGColor()
{
  return bgColor;
}

}// namespace renderer