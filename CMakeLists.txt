cmake_minimum_required(VERSION 2.8)
project(ModeloMisturaGaussianas)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include(CTest)
enable_testing()

add_executable(ModeloMisturaGaussianas modelo.cpp Gaussiana.cpp Pixel.cpp)
target_link_libraries( ModeloMisturaGaussianas ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(GCC_COVERAGE_COMPILE_FLAGS "-Os")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include(CPack)
