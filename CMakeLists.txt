cmake_minimum_required(VERSION 3.1)

project(CSGraphicsStarterCode, CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy-13)
  if(CLANGTIDY)
    set(CMAKE_C_CLANG_TIDY ${CLANGTIDY})
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
  else()
    message(SEND_ERROR "clang-tidy could not be located.")
  endif()
endif()


# ######################################################################################################################
# Apple from NVIDIA OptiX CMake/Macros.cmake
# ######################################################################################################################
# Appends VAL to the string contained in STR
macro(APPEND_TO_STRING STR VAL)
  if(NOT
     "${ARGN}"
     STREQUAL
     "")
    message(SEND_ERROR "APPEND_TO_STRING takes only a single argument to append.  Offending args: ${ARGN}")
  endif()
  # You need to double ${} STR to get the value.  The first one gets the variable, the second one gets the value.
  if(${STR})
    set(${STR} "${${STR}} ${VAL}")
  else()
    set(${STR} "${VAL}")
  endif()
endmacro(APPEND_TO_STRING)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ######################################################################################################################
# Apple from NVIDIA OptiX CMake/ConfigCompilerFlags.cmake
# ######################################################################################################################
if(APPLE)
  if(USING_CLANG_CXX)

    append_to_string(CXX_FLAGS "-mmacosx-version-min=10.8")
  endif()
  append_to_string(GCC_ARCH "nocona")
  append_to_string(GCC_ARCH "prescott")
  append_to_string(GCC_OPT "-msse -msse2 -msse3")
  if(USING_GNU_C OR USING_GNU_CXX)
    append_to_string(GCC_OPT "-mfpmath=sse")
  endif()
endif(APPLE)

# --------------------------------------------------------------------
# PNG and ZLIB
#
# This macro will attempt to locate the PNG include directories, link directories and libraries. The INCLUDE_DIRECTORIES
# macro adds the resulting include directories to the search path.
# --------------------------------------------------------------------
# INCLUDE_DIRECTORIES(/usr/local/Cellar/libpng/1.6.36/include/libpng16)
# LINK_DIRECTORIES(/usr/local/Cellar/libpng/1.6.36/lib) SET(PNG_LIBRARY png) SET(PNG_LIBRARIES
# /usr/local/Cellar/libpng/1.6.36/lib/libpng.dylib ) SET(PNG_DIR /usr/local/Cellar/libpng/1.6.36) find_package(PNG
# REQUIRED PATHS /usr/local/Cellar/libpng/1.6.36 NO_DEFAULT_PATH)
find_package(PNG REQUIRED)
if(PNG_FOUND)
  message(STATUS "PNG Version: ${PNG_VERSION_STRING}, Includes: ${PNG_INCLUDE_DIR}, Libs: ${PNG_LIBRARIES}")
  include_directories(${PNG_INCLUDE_DIR})
else(PNG_FOUND)
  message(STATUS "Could not find the PNG Libraries!")
endif(PNG_FOUND)

# Search for the OptiX libraries and include files. find_package(OptiX REQUIRED)

# FROM https://github.com/nlohmann/json

# Typically you don't care so much for a third party library's tests to be run from your own project's code.
set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")

# If you only include this third party in PRIVATE source files, you do not need to install it when your main project
# gets installed. set(JSON_Install OFF CACHE INTERNAL "")

# Don't use include(nlohmann_json/CMakeLists.txt) since that carries with it unintended consequences that will break the
# build.  It's generally discouraged (although not necessarily well documented as such) to use include(...) for pulling
# in other CMake projects anyways.
add_subdirectory(json-develop)

# target_link_libraries(foo PRIVATE nlohmann_json::nlohmann_json)

# Add the path to the OptiX headers to our include paths.
include_directories(# "${OptiX_INCLUDE}"
                    "json-develop/include")

# --------------------------------------------------------------------
# OpenGL Related Components
# --------------------------------------------------------------------
find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)
message(STATUS "GLEW: incs= ${GLEW_INCLUDE_DIR}, libs= ${GLEW_LIBRARIES}")
include_directories(${GLEW_INCLUDE_DIR})

# We'll enable this later if possible
find_package(Vulkan REQUIRED)

# To be able to include the GLFW header from your code, you need to tell the compiler where to find it.
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw-master)

# Once GLFW has been added to the project, the GLFW_LIBRARIES cache variable contains all link-time dependencies of GLFW
# as it is currently configured. To link against GLFW, link against them and the glfw target.
include_directories(${CMAKE_SOURCE_DIR}/glfw-master/include)
message(STATUS "${GLFW_LIBRARIES}")
set(GLFW_STATIC_LIBRARIES "${GLFW_LIBRARIES}")

include_directories(${CMAKE_SOURCE_DIR}/glm-0.9.9.9)

# ----------------------------------------------------------
# Boost
#
# This section tests for Boost support on the system. Boost is required as it is used heavily with this code. Boost also
# allows the code to be nicely portable across Operating Systems.
# ----------------------------------------------------------
# SET (Boost_MULTITHREADED TRUE)

# If you want to get more info on what the Find Boost macro is doing... SET(Boost_DEBUG 1)

# Necessary to get Win32 version to work, plus, not a bad idea to link statically for our purposes.
if(WIN32)
  set(Boost_USE_STATIC_LIBS TRUE)
endif(WIN32)

find_package(
  Boost REQUIRED
  COMPONENTS date_time
             program_options
             filesystem
             system
             thread
             unit_test_framework
             chrono
             timer)
if(${Boost_FOUND})
  include_directories(${Boost_INCLUDE_DIR})
  message(STATUS "Boost Libs: ${Boost_LIBRARIES}")
endif()

# Add the src directory to build the libsive-util.a library.
add_subdirectory(src)

# If you want, we can also compile the tests directory that are essentially examples for how to use some of the classes
# and code.
add_subdirectory(examples)

#
# Renderer codes
#
# You will link your renderer library directory here
# add_subdirectory(renderer)

#
# OpenGL Example
#
# This builds a simple OpenGL example that you can use to get started with OpenGL.
#
add_subdirectory(OpenGL)

# We'll enable this later if possible
add_subdirectory(Vulkan)

#
# Unit Tests - by enabling testing with cmake, we can create a target that lets unit tests be run. After re-building
# yourproject with ENABLE_TESTING called, a make target, called test will be enabled. You can then type
#
# make test
#
# to perform the unit tests. See the CMakeLists.txt file in the utests directory for more details. Also, see the unit
# test .cpp files in the utests directory for examples on using Boost's unit test system.
#
enable_testing()
add_subdirectory(utests)
