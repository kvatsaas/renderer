#include <cstdlib>
#include <iostream>
#include <vector>

#include <glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

#include "ExampleTriangles.h"

double FPS = 0.0;

glm::mat4 modelMatrix;

double xRotation = 0.0;
double yRotation = 0.0;
double zRotation = 0.0;
double rotationRate = 1.0;
bool rotationChange = false;

const std::string f_passthrough = "fragmentShader_passthrough.glsl";
const std::string f_perVertex = "fragmentShader_perVertex.glsl";
const std::string v_passthrough = "vertexShader_passthrough.glsl";
const std::string v_perVertexColor = "vertexShader_perVertexColor.glsl";
const std::string v_perVertexLambertian = "vertexShader_perVertexLambertianShading.glsl";
const std::string v_perVertexNormal = "vertexShader_perVertexNormalShading.glsl";

int CheckGLErrors(const char *s)
{
  int errCount = 0;

  return errCount;
}

/* Handler for key presses
 * t: print FPS
 * m: rotate +x
 * n: rotate -x
 * k: rotate +y
 * j: rotate -y
 * o: rotate +z
 * i: rotate -z
 * l: reset all to 0
 */
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  {
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
      std::cout << "FPS: " << FPS << std::endl;
    } else if (key == GLFW_KEY_M && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      xRotation += rotationRate;
      rotationChange = true;
    } else if (key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      xRotation -= rotationRate;
      rotationChange = true;
    } else if (key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      yRotation += rotationRate;
      rotationChange = true;
    } else if (key == GLFW_KEY_J && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      yRotation -= rotationRate;
      rotationChange = true;
    } else if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      zRotation += rotationRate;
      rotationChange = true;
    } else if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      zRotation -= rotationRate;
      rotationChange = true;
    } else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
      xRotation = 0;
      yRotation = 0;
      zRotation = 0;
      rotationChange = true;
    }
  }
}

int main(void)
{
  /* Initialize the library */
  if (!glfwInit()) {
    exit(-1);
  }

  // throw std::runtime_error("Error! initialization of glfw failed!");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  int winWidth = 1200;
  float aspectRatio = 1.00f;// winWidth / (float)winHeight;
  int winHeight = winWidth / aspectRatio;

  // non-canonical coordinate setup
  float left = -7.0f;
  float right = 7.0f;
  float bottom = -7.0f;
  float top = 7.0f;
  float near = -10.0f;
  float far = 10.0f;

  GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "OpenGL Example", NULL, NULL);
  if (!window) {
    std::cerr << "GLFW did not create a window!" << std::endl;

    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "GLEW Error! glewInit failed, exiting." << std::endl;
    exit(EXIT_FAILURE);
  }

  /********************/
  /* Begin glGet demo */
  /********************/
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  const GLubyte *vendor = glGetString(GL_VENDOR);
  const GLubyte *shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;
  std::cout << "Vendor: " << vendor << std::endl;
  std::cout << "Shading language version: " << shading << std::endl;

  GLint major_version, minor_version, max_texture, depth_test;
  glGetIntegerv(GL_MAJOR_VERSION, &major_version);
  glGetIntegerv(GL_MINOR_VERSION, &minor_version);
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture);
  glGetIntegerv(GL_DEPTH_TEST, &depth_test);
  std::cout << "OpenGL Major Version: " << major_version << std::endl;
  std::cout << "OpenGL Minor Version: " << minor_version << std::endl;
  std::cout << "OpenGL Max Texture Size: " << max_texture << std::endl;
  std::cout << "OpenGL Depth Test Enabled: " << depth_test << std::endl;
  /******************/
  /* End glGet demo */
  /******************/

  /**********************/
  /* Begin VBO/VAO demo */
  /**********************/
  // get a VBO identifier from the driver
  GLuint triangleVBO;
  glGenBuffers(1, &triangleVBO);

  // bind the buffer id
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

  // create 3D vertex data as a vector of floats
  std::vector<float> host_VertexBuffer = MiniMesh();
  int numBytes = host_VertexBuffer.size() * sizeof(float);
  int stride = 9;
  int attribCount = host_VertexBuffer.size() / stride;

  // set up uniform variables
  glm::mat4 projMatrix = glm::ortho(left, right, bottom, top, near, far);
  glm::vec3 light(0.0f, 0.0f, -10.0f);
  glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
  glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
  glm::vec3 zAxis(0.0f, 0.0f, 1.0f);
  modelMatrix = glm::rotate((glm::mediump_f32)glm::radians(xRotation), yAxis);

  // copy vertex data from host to device (CPU memory to GPU memory)
  glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);

  // clear data from host
  host_VertexBuffer.clear();

  // get a VAO identifier and bind it
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // enable attributes 0 (position), 1 (color), and 2 (normal)
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  // bind VBO to VAO and associate its vertex data
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), 0);// position
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid *)12);// color
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid *)24);// normal

  // unbind VAO
  glBindVertexArray(0);

  // set up shaders using Prof. Willemsen's provided GLSLObject class
  sivelab::GLSLObject shader;
  shader.addShader(v_perVertexNormal, sivelab::GLSLObject::VERTEX_SHADER);
  shader.addShader(f_perVertex, sivelab::GLSLObject::FRAGMENT_SHADER);
  shader.createProgram();

  // create reference to projMatrix variable in shader
  GLuint projMatrixID = shader.createUniform("projMatrix");
  GLuint modelMatrixID = shader.createUniform("modelMatrix");
  GLuint lightID = shader.createUniform("light");

  //activate shader so we can set uniform variable data, then deactivate
  shader.activate();

  glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix));
  glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
  glUniform3fv(lightID, 1, glm::value_ptr(light));

  shader.deactivate();
  /********************/
  /* End VBO/VAO demo */
  /********************/

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0);
  glfwSetKeyCallback(window, key_callback);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

  double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */

    endFrameTime = glfwGetTime();
    timeDiff = endFrameTime - startFrameTime;
    FPS = 1.0 / timeDiff;
    //std::cout << "FPS: " << FPS << std::endl;
    startFrameTime = glfwGetTime();

    // Clear the window's buffer (or clear the screen to our
    // background color)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Begin render VBO/VAO demo */
    shader.activate();// bind shader
    //update rotation if needed
    if (rotationChange) {
      modelMatrix = glm::rotate(
        glm::rotate(
          glm::rotate(
            (glm::mediump_f32)glm::radians(zRotation),
            zAxis),
          (glm::mediump_f32)glm::radians(yRotation), 
          yAxis),
        (glm::mediump_f32)glm::radians(xRotation),
        xAxis);
      glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
      rotationChange = false;
    }

    glBindVertexArray(VAO);// bind VAO
    glDrawArrays(GL_TRIANGLES, 0, attribCount);// tell OpenGL to render
    glBindVertexArray(0);// unbind VAO
    shader.deactivate();// unbind shader
    /* End render VBO/VAO demo */

    // Swap the front and back buffers
    glfwSwapInterval(0);
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, 1);
  }

  glfwTerminate();
  return 0;
}
