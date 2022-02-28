#include "SceneContainer.h"

namespace renderer {
SceneContainer::SceneContainer()
  : cameras(), shaders(), shapes(), bgColor(), default_nx(100), default_ny(100) {}

SceneContainer::SceneContainer(int nx, int ny)
  : cameras(), shaders(), shapes(), bgColor(), default_nx(nx), default_ny(ny) {}

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

void SceneContainer::set_nx(float nx)
{
  default_nx = nx;
}

void SceneContainer::set_ny(float ny)
{
  default_ny = ny;
}

const std::vector<Camera *> &SceneContainer::getCameras()
{
  return cameras;
}

const std::vector<Light *> &SceneContainer::getLights()
{
  return lights;
}

std::vector<Light *> SceneContainer::getVisibleLights(Vector3D point, const Shape *sPtr)
{
  auto visibleLights = std::vector<Light *>();

  for (int i = 0; i < lights.size(); i++) {
    bool blocked = false;
    auto lightRayDir = (lights[i]->getPosition() - point);// light direction
    float tmax = 1.0;
    HitStructure dummy;
    for (int j = 0; j < shapes.size(); j++) {
      if (shapes[j] == sPtr)
        continue;
      if (shapes[j]->closestHit(Ray(point, lightRayDir), FLT_EPSILON, tmax, dummy)) {
        blocked = true;
        break;
      }
    }
    if (!blocked)
      visibleLights.push_back(lights[i]);
  }

  return visibleLights;
}

Shader *SceneContainer::getShader(std::string name)
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

float SceneContainer::get_nx() const
{
  return default_nx;
}

float SceneContainer::get_ny() const
{
  return default_ny;
}

}// namespace renderer