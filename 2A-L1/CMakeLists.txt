cmake_minimum_required(VERSION 3.7)
project(2A_L1)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES src/blend2Images.cpp src/colorPlanes.cpp src/main.cpp include/blend2images.h include/colorPlanes.h)
add_executable(2A_L1 ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries( 2A_L1 ${OpenCV_LIBS} )