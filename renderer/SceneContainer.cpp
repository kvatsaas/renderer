#include "SceneContainer.h"

namespace renderer {
SceneContainer::SceneContainer()
  : cameras(), shaders(), shapes() {}

void SceneContainer::addCamera(Camera &c)
{
  cameras.push_back(&c);
}

void SceneContainer::addLight(Light &l)
{
  lights.push_back(&l);
}

void SceneContainer::addShader(Shader &s)
{
  shaders.insert({ s.getName(), &s });
}

void SceneContainer::addShape(Shape &s)
{
  shapes.push_back(&s);
}

}// namespace renderer