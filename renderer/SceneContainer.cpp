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

std::vector<Light *> SceneContainer::getVisibleLights(Vector3D point, int depth, boost::optional<std::vector<std::pair<float, float>>> jitter, int r)
{
  auto visibleLights = std::vector<Light *>();

  for (int i = 0; i < lights.size(); i++) {
    if (lights[i]->isVisibleFrom(point, depth, *this, jitter, r))
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

bool SceneContainer::anyHit(Ray r, float tmin, float tmax, int depth)
{
  return rootNode.hit(r, tmin, tmax, depth);
}

Vector3D SceneContainer::rayColor(Ray &r, float tmin, float tmax, int depth)
{
  if (depth >= maxDepth)
    return bgColor;

  boost::optional<std::vector<std::pair<float, float>>> dummyJitter;
  HitStructure h;
  bool hitOccurred = rootNode.closestHit(r, tmin, tmax, h, depth);

  if (hitOccurred)
    return h.getShader()->apply(h, *this, depth, dummyJitter, -1);
  else
    return bgColor;
}

Vector3D SceneContainer::rayColor(std::vector<Ray> &rays, float tmin, float tmax, int depth, std::vector<std::pair<float, float>> &jitterShadows)
{
  if (depth >= maxDepth)
    return bgColor;

  auto color = Vector3D();
  for (int r = 0; r < rays.size(); r++) {
    HitStructure h;
    float local_tmax = tmax;
    bool hitOccurred = rootNode.closestHit(rays[r], tmin, local_tmax, h, depth);
    if (hitOccurred)
      color += h.getShader()->apply(h, *this, depth, jitterShadows, r);
    else
      color += bgColor;
  }

  color /= rays.size();
  return color;
}

}// namespace renderer
