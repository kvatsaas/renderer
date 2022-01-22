include_directories(${CMAKE_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${Vulkan_INCLUDE_DIRS})
LINK_LIBRARIES(${Vulkan_LIBRARY}) 

add_executable (basicCode
  basicCode.cpp
)
target_link_libraries (basicCode ${GLEW_LIBRARIES})
target_link_libraries (basicCode glfw ${GLFW_STATIC_LIBRARIES})
target_link_libraries (basicCode ${Vulkan_LIBRARIES})
target_link_libraries (basicCode ${PNG_LIBRARIES})
target_link_libraries (basicCode ${ZLIB_LIBRARIES})
