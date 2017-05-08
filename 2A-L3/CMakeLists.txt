cmake_minimum_required(VERSION 3.7)
project(2A_L3)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES src/main.cpp include/applyMedianFilter.h include/exploreEdgeOptions.h src/applyMedianFilter.cpp src/exploreEdgeOptions.cpp)
add_executable(2A_L3 ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries( 2A_L3 ${OpenCV_LIBS} )