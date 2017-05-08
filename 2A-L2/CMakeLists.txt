cmake_minimum_required(VERSION 3.7)
project(2A_L2)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES src/main.cpp)
add_executable(2A_L2 ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( 2A_L2 ${OpenCV_LIBS} )