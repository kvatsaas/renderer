#pragma once
#include <map>
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Shader.h"
#include "Shape.h"
#include "InstancedObject.h"
#include "BVHNode.h"
#include <boost/optional/optional.hpp>

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
  */
  SceneContainer(int nx, int ny);

  /**
   * @brief Builds the tree of BVHNodes. Should only be called once all shapes are added.
  */
  void buildBVHTree();

  /**
   * @brief Adds a camera to the SceneContainer
   * @param c A pointer to the camera to add
  */
  void addCamera(Camera *c);

  /**
   * @brief Adds a light to the SceneContainer
   * @param l A pointer to the light to add
  */
  void addLight(Light *l);

  /**
   * @brief Adds a shader to the SceneContainer
   * @param s A pointer to the shader to add
  */
  void addShader(Shader *s);

  /**
   * @brief Adds a shape to the SceneContainer
   * @param s A pointer to the shape to add
  */
  void addShape(Shape *s);

  /**
   * @brief Adds an instanced object to the SceneContainer
   * @param s A pointer to the instanced object to add
  */
  void addInstancedObject(Shape *s);

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
   * @brief Sets the n value (sqrt of rpp)
   * @param n The n value
  */
  void set_n(int n);

  /**
   * @brief Setter for the path to the scene file
   * @param path The path
  */
  void setPathToSceneFile(std::string path);

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
   * @brief Getter for a single shader
   * @param name The name of the shader
   * @return The requested shader, or nullptr if it does not exist
  */
  Shader *getShader(std::string name);

  /**
   * @brief Getter for the shapes in the scene
   * @return A vector of pointers to shapes
  */
  const std::vector<Shape *> &getShapes();

  /**
   * @brief Getter for the instanced objects in the scene
   * @return A map of instanced object pointers mapped by their names
  */
  const std::map<std::string, Shape *> &getInstancedObjects();

  /**
   * @brief Getter for a single instanced object
   * @param name The name of the instanced object
   * @return The requested instanced object, or nullptr if it does not exist
  */
  Shape *getInstancedObject(std::string name);

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
   * @brief Getter for the root BVH node
   * @return The root BVH node
  */
  BVHNode getRoot();

  /**
   * @brief Gets the max recursive depth for rayColor
   * @return The max depth
  */
  int getMaxDepth();

  /**
   * @brief Getter for the n value (sqrt of rpp)
   * @return The n value
  */
  int get_n();

  /**
   * @brief Getter for the path to the scene file
   * @return The path
  */
  std::string getPathToSceneFile();

  /**
   * @brief Gets all lights visible from a given point
   * @param point The point
   * @param depth The current reflection depth
   * @param jitter The optional shadow jitter values
   * @param r The current ray number for antialiasing. Use -1 if not using AA
   * @return A vector of pointers to lights
  */
  std::vector<Light *> getVisibleLights(Vector3D point, int depth, boost::optional<std::vector<std::pair<float, float>>>, int r);

  /**
   * @brief Determines whether the given ray hits any shape in the scene
   * @param r The ray
   * @param tmin The minimum tvalue
   * @param tmax The maximum tvalue
   * @param depth The current reflection depth
   * @return 
  */
  bool anyHit(Ray r, float tmin, float tmax, int depth);

  /**
   * @brief Determines the color hit by the given ray in this scene
   * @param r The ray
   * @param tmin The minimum tvalue
   * @param tmax The maximum tvalue
   * @param depth The current recursive depth
   * @return The color
  */
  Vector3D rayColor(Ray &r, float tmin, float tmax, int depth);

  /**
   * @brief Determines the color hit by the given ray samples in this scene. AA aware version of rayColor
   * @param rays A vector of sample rays
   * @param tmin The minimum tvalue
   * @param tmax The maximum tvalue
   * @param depth The current recursive depth
   * @param jitterShadows The shadow jitter values
   * @return The color
  */
  Vector3D rayColor(std::vector<Ray> &rays, float tmin, float tmax, int depth, std::vector<std::pair<float, float>> &jitterShadows);

protected:
  std::vector<Camera *> cameras;
  std::vector<Light *> lights;
  std::map<std::string, Shader *> shaders;
  std::vector<Shape *> shapes;
  std::map<std::string, Shape *> instancedObjects;
  BVHNode rootNode;
  Vector3D bgColor;
  float default_nx, default_ny;
  int maxDepth = 3, n = 0;
  std::string pathToSceneFile;
};

}// namespace renderer
