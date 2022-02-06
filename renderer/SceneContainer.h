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
  /**
   * @brief Creates an empty SceneContainer
  */
  SceneContainer();

  /**
   * @brief Adds a camera to the SceneContainer
   * @param c A reference to the camera to add
  */
  void addCamera(Camera &c);

  /**
   * @brief Adds a light to the SceneContainer
   * @param l A reference to the light to add
  */
  void addLight(Light &l);

  /**
   * @brief Adds a shader to the SceneContainer
   * @param s A reference to the cashadermera to add
  */
  void addShader(Shader &s);

  /**
   * @brief Adds a shape to the SceneContainer
   * @param s A reference to the shape to add
  */
  void addShape(Shape &s);

protected:
  std::vector<Camera *> cameras;
  std::vector<Light *> lights;
  std::map<std::string, Shader *> shaders;
  std::vector<Shape *> shapes;
};

}// namespace renderer
