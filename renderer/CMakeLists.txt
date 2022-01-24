add_library(renderer Vector3D.cpp Vector3D.h Framebuffer.cpp Framebuffer.h)

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