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
   * @brief Creates an empty SceneContainer with default nx/ny of 100.
  */
  SceneContainer();

  /**
   * @brief Creates an empty SceneContainer with the given nx/ny and a maximum depth
   *        that specifies the number of times a ray can be reflected
   * @param nx The default width for output images
   * @param ny The default height for output images
   * @param d The maximum recursive depth; defaults to 3
  */
  SceneContainer(int nx, int ny, int d = 3);

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
   * @brief Sets a background color
   * @param bg A color
  */
  void setBGColor(Vector3D bg);

  /**
   * @brief Sets the default nx value
   * @param ny The default width for output images
  */
  void set_nx(float nx);

  /**
   * @brief Sets the default ny value
   * @param nx The default height for output images
  */
  void set_ny(float ny);

  /**
   * @brief Sets the max recursive depth for rayColor
   * @param nx The max depth
  */
  void setMaxDepth(int d);

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
   * @brief Gets all lights visible from a given point on a shape
   * @param point The point in question
   * @param sPtr A pointer to the shape in question
   * @return A vector of pointers to lights
  */
  std::vector<Light *> getVisibleLights(Vector3D point, const Shape *sPtr = nullptr);

  /**
   * @brief Getter for a single shader
   * @param name The name of the shader
   * @return The requested shader, or nullptr if it does not exist
  */
  Shader *getShader(std::string name);

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

  /**
   * @brief Getter for the background color
   * @return The background color
  */
  const Vector3D &getBGColor();

  /**
   * @brief Gets the default nx value
   * @return The default width for output images
  */
  float get_nx() const;

  /**
   * @brief Gets the default ny value
   * @return The default height for output images
  */
  float get_ny() const;

  /**
   * @brief Gets the max recursive depth for rayColor
   * @return The max depth
  */
  int getMaxDepth(int d);

  /**
   * @brief Determines whether the given ray hits any shape in the scene
   * @param r The ray
   * @param tmin The minimum tvalue
   * @param tmax The maximum tvalue
   * @param sPtr An optional pointer to a shape to be ignored 
   * @return 
  */
  bool anyHit(Ray r, float tmin, float tmax, const Shape *sPtr = nullptr);

  /**
   * @brief Determines the color hit by the given ray in this scene
   * @param r The ray
   * @param tmin The minimum tvalue
   * @param tmax The maximum tvalue
   * @param depth The current recursive depth
   * @return The color
  */
  Vector3D rayColor(Ray &r, float tmin, float tmax, int depth);

protected:
  std::vector<Camera *> cameras;
  std::vector<Light *> lights;
  std::map<std::string, Shader *> shaders;
  std::vector<Shape *> shapes;
  Vector3D bgColor;
  float default_nx, default_ny;
  int maxDepth;
};

}// namespace renderer
