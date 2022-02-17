add_library(renderer
	Camera.cpp Camera.h
	CoordSys.cpp CoordSys.h
	Framebuffer.cpp Framebuffer.h
	HitStructure.cpp HitStructure.h
	Light.h 
	NormalShader.cpp NormalShader.h
	OrthographicCamera.cpp OrthographicCamera.h 
	PerspectiveCamera.cpp PerspectiveCamera.h
	PointLight.cpp PointLight.h
	Ray.cpp Ray.h
	Renderer.cpp Renderer.h
	SceneContainer.cpp SceneContainer.h
	Shader.cpp Shader.h
	Shape.cpp Shape.h
	Sphere.cpp Sphere.h
	Triangle.cpp Triangle.h
	Vector3D.cpp Vector3D.h
	WhittedRayTracer.cpp WhittedRayTracer.h)

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

add_executable (test_RayVisualization
  test_RayVisualization.cpp
)
target_link_libraries (test_RayVisualization renderer)
target_link_libraries (test_RayVisualization ${Boost_LIBRARIES})
target_link_libraries (test_RayVisualization ${PNG_LIBRARIES})
target_link_libraries (test_RayVisualization ${ZLIB_LIBRARIES})

add_executable (test_Renderer
	test_Renderer.cpp
)
target_link_libraries (test_Renderer renderer)
target_link_libraries (test_Renderer ${Boost_LIBRARIES})
target_link_libraries (test_Renderer ${PNG_LIBRARIES})
target_link_libraries (test_Renderer ${ZLIB_LIBRARIES})

add_executable (test_ColorRamp
	test_ColorRamp.cpp
)
target_link_libraries (test_ColorRamp renderer)
target_link_libraries (test_ColorRamp ${Boost_LIBRARIES})
target_link_libraries (test_ColorRamp ${PNG_LIBRARIES})
target_link_libraries (test_ColorRamp ${ZLIB_LIBRARIES})