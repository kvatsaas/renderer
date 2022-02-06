add_library(renderer Camera.h CoordSys.cpp CoordSys.h Framebuffer.cpp Framebuffer.h Light.h OrthographicCamera.cpp OrthographicCamera.h PerspectiveCamera.cpp PerspectiveCamera.h PointLight.cpp PointLight.h Ray.cpp Ray.h SceneContainer.cpp SceneContainer.h Shader.h Shape.h Triangle.cpp Triangle.h Vector3D.cpp Vector3D.h)

add_executable(test_Vector3D
  test_Vector3D.cpp
)
target_link_libraries(test_Vector3D renderer)

add_executable (test_Framebuffer
  test_Framebuffer.cpp
)
target_link_libraries (test_Framebuffer renderer)
target_link_libraries (test_Framebuffer sive-util)
target_link_libraries (test_Framebuffer ${Boost_LIBRARIES})
target_link_libraries (test_Framebuffer ${PNG_LIBRARIES})
target_link_libraries (test_Framebuffer ${ZLIB_LIBRARIES})

add_executable (test_Raytracer
  test_Raytracer.cpp
)
target_link_libraries (test_Raytracer renderer)
target_link_libraries (test_Raytracer ${Boost_LIBRARIES})
target_link_libraries (test_Raytracer ${PNG_LIBRARIES})
target_link_libraries (test_Raytracer ${ZLIB_LIBRARIES})