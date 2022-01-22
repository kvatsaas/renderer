# 
# Adds the src directory to the include search
# path. ${CMAKE_SOURCE_DIR} is prefixed to allow the files in the
# utest directory to correctly include the relative reference to the
# src files.
#
include_directories(${CMAKE_SOURCE_DIR}/src)
# include_directories(${CMAKE_SOURCE_DIR}/raytrace)

add_executable(test_Timer
  test_Timer.cpp
)
target_link_libraries(test_Timer sive-util)
IF(WIN32)
   target_link_libraries(test_Timer Winmm)
ENDIF(WIN32)

add_executable(sphereTest
  sphereTest.cpp
)
target_link_libraries(sphereTest sive-util)


add_executable(test_pngWrite
  test_pngWrite.cpp
)
target_link_libraries(test_pngWrite sive-util)
target_link_libraries(test_pngWrite ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_pngWrite ${PNG_LIBRARY})
target_link_libraries(test_pngWrite ${ZLIB_LIBRARY})

add_executable(test_readPNGFile
  test_readPNGFile.cpp
)
target_link_libraries(test_readPNGFile sive-util)
target_link_libraries(test_readPNGFile ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_readPNGFile ${PNG_LIBRARY})
target_link_libraries(test_readPNGFile ${ZLIB_LIBRARY})

add_executable(test_XMLSceneParse
  SceneFile_Instancer.h SceneFile_Instancer.cpp
  test_XMLSceneParse.cpp
)
target_link_libraries(test_XMLSceneParse sive-util)
target_link_libraries(test_XMLSceneParse ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_XMLSceneParse ${PNG_LIBRARY})
target_link_libraries(test_XMLSceneParse ${ZLIB_LIBRARY})


add_executable(genRandomVals
  genRandomVals.cpp
)
target_link_libraries(genRandomVals sive-util)
target_link_libraries(genRandomVals ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(genRandomVals ${PNG_LIBRARY})
target_link_libraries(genRandomVals ${ZLIB_LIBRARY})
