
add_library(renderer
	AABoundingBox.cpp AABoundingBox.h
	AreaLight.cpp AreaLight.h
	BlinnPhongMirroredShader.cpp BlinnPhongMirroredShader.h
	BlinnPhongShader.cpp BlinnPhongShader.h
	Box.cpp Box.h
	BVHNode.cpp BVHNode.h
	Camera.cpp Camera.h
	DiffuseShader.cpp DiffuseShader.h
	CoordSys.cpp CoordSys.h
	Framebuffer.cpp Framebuffer.h
	GlazeShader.cpp GlazeShader.h
	HitStructure.cpp HitStructure.h
	InstancedObject.cpp InstancedObject.h
	jsonParser.cpp
	LambertianShader.cpp LambertianShader.h
	Light.cpp Light.h
	OBJMesh.cpp OBJMesh.h
	MirrorShader.cpp MirrorShader.h
	NormalShader.cpp NormalShader.h
	OrthographicCamera.cpp OrthographicCamera.h
	ParallelWhittedRayTracer.cpp ParallelWhittedRayTracer.h
	PerspectiveCamera.cpp PerspectiveCamera.h
	PhongShader.cpp PhongShader.h
	PointLight.cpp PointLight.h
	Ray.cpp Ray.h
	Renderer.cpp Renderer.h
	SceneContainer.cpp SceneContainer.h
	Shader.cpp Shader.h
	shaders.h
	Shape.cpp Shape.h
	shapes.h
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

add_executable (test_RenderJSON
	test_RenderJSON.cpp
)
target_link_libraries (test_RenderJSON renderer)
target_link_libraries (test_RenderJSON sive-util)
target_link_libraries (test_RenderJSON ${Boost_LIBRARIES})
target_link_libraries (test_RenderJSON ${PNG_LIBRARIES})
target_link_libraries (test_RenderJSON ${ZLIB_LIBRARIES})

add_executable (test_RasterizeTriangle
	test_RasterizeTriangle.cpp
)
target_link_libraries (test_RasterizeTriangle renderer)
target_link_libraries (test_RasterizeTriangle ${Boost_LIBRARIES})
target_link_libraries (test_RasterizeTriangle ${PNG_LIBRARIES})
target_link_libraries (test_RasterizeTriangle ${ZLIB_LIBRARIES})

add_executable (test_ColorRamp
	test_ColorRamp.cpp
)
target_link_libraries (test_ColorRamp renderer)
target_link_libraries (test_ColorRamp ${Boost_LIBRARIES})
target_link_libraries (test_ColorRamp ${PNG_LIBRARIES})
target_link_libraries (test_ColorRamp ${ZLIB_LIBRARIES})

add_executable (patterns
	patterns.cpp
)
target_link_libraries (patterns renderer)
target_link_libraries (patterns ${Boost_LIBRARIES})
target_link_libraries (patterns ${PNG_LIBRARIES})
target_link_libraries (patterns ${ZLIB_LIBRARIES})
