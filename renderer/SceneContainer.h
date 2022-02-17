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
   * @param c A pointer to the camera to add
  */
  void addCamera(Camera *c);

  /**
   * @brief Adds a light to the SceneContainer
   * @param l A refepointerrence to the light to add
  */
  void addLight(Light *l);

  /**
   * @brief Adds a shader to the SceneContainer
   * @param s A pointer to the cashadermera to add
  */
  void addShader(Shader *s);

  /**
   * @brief Adds a shape to the SceneContainer
   * @param s A pointer to the shape to add
  */
  void addShape(Shape *s);

  /**
   * @brief Getter for the cameras in the scene
   * @return A vector of pointers to cameras
  */
  const std::vector<Camera *> &getCameras();

  /**
   * @brief Getter for the lights in the scene
   * @return A vector of pointers to lights
  */
  const std::vector<Light *> &getLights();

  /**
   * @brief Getter for the shaders in the scene
   * @return A map of shader pointers mapped by their names
  */
  const std::map<std::string, Shader *> &getShaders();

  /**
   * @brief Getter for the shapes in the scene
   * @return A vector of pointers to shapes
  */
  const std::vector<Shape *> &getShapes();

protected:
  std::vector<Camera *> cameras;
  std::vector<Light *> lights;
  std::map<std::string, Shader *> shaders;
  std::vector<Shape *> shapes;
};

}// namespace renderer
