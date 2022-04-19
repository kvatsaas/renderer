#include <cfloat>
#include "SceneContainer.h"

namespace renderer {
SceneContainer::SceneContainer()
  : cameras(), shaders(), shapes(), bgColor(), default_nx(100), default_ny(100) {}

SceneContainer::SceneContainer(int nx, int ny)
  : cameras(), shaders(), shapes(), bgColor(), default_nx(nx), default_ny(ny) {}

void SceneContainer::buildBVHTree()
{
  rootNode = BVHNode(shapes);
}

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

void SceneContainer::setMaxDepth(int d)
{
  maxDepth = d;
}

void SceneContainer::set_n(int n)
{
  this->n = n;
}

const std::vector<Camera *> &SceneContainer::getCameras()
{
  return cameras;
}

const std::vector<Light *> &SceneContainer::getLights()
{
  return lights;
}

std::vector<Light *> SceneContainer::getVisibleLights(Vector3D point, int depth)
{
  auto visibleLights = std::vector<Light *>();

  for (int i = 0; i < lights.size(); i++) {
    auto lightRayDir = (lights[i]->getPosition() - point);// light direction
    if (!anyHit(Ray(point, lightRayDir), 0.0001f, 1.0f, depth))
      visibleLights.push_back(lights[i]);
  }

  return visibleLights;
}

void SceneContainer::gatherLightSamples(Vector3D point, int depth, std::vector<Vector3D> &directions, std::vector<Vector3D> &intensities)
{
  for (int i = 0; i < lights.size(); i++)
    lights[i]->getLightSamples(point, depth, *this, directions, intensities);
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

BVHNode SceneContainer::getRoot()
{
  return rootNode;
}

int SceneContainer::getMaxDepth()
{
  return maxDepth;
}

int SceneContainer::get_n()
{
  return n;
}

bool SceneContainer::anyHit(Ray r, float tmin, float tmax, int depth)
{
  //pre-BVH logic
  /*for (int j = 0; j < shapes.size(); j++) {
    if (shapes[j] == sPtr)
      continue;
    if (shapes[j]->hit(r, tmin, tmax))
      return true;
  }
  return false;*/

  return rootNode.hit(r, tmin, tmax, depth);
}

Vector3D SceneContainer::rayColor(Ray &r, float tmin, float tmax, int depth)
{
  if (depth >= maxDepth)
    return bgColor;

  HitStructure h;
  bool hitOccurred = rootNode.closestHit(r, tmin, tmax, h, depth);
  //pre-BVH logic
  /*for (int s = 0; s < shapes.size(); s++)
    if (shapes[s]->closestHit(r, tmin, tmax, h))
      hitOccurred = true;*/

  if (hitOccurred)
    return h.getShader()->apply(h, *this, depth);
  else
    return bgColor;
}

}// namespace renderer
