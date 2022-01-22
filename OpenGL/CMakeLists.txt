include_directories(${CMAKE_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries (${OPENGL_LIBRARY})

add_executable (glfwExample
  glfwExample.cpp 
  GLSL.cpp GLSL.h
)
target_link_libraries (glfwExample ${GLEW_LIBRARIES})
target_link_libraries (glfwExample glfw ${GLFW_STATIC_LIBRARIES})
target_link_libraries (glfwExample ${PNG_LIBRARIES})
target_link_libraries (glfwExample ${ZLIB_LIBRARIES})

