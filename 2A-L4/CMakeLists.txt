cmake_minimum_required(VERSION 3.7)
project(2A-L4)

find_package( dlib REQUIRED )
find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 11)

set(findTemplate1D_src src/findTemplate1D.cpp)
set(findTemplate2D_src src/findTemplate2D.cpp)

add_executable(findTemplate1D ${findTemplate1D_src})
add_executable(findTemplate2D ${findTemplate2D_src})

TARGET_LINK_LIBRARIES(findTemplate1D ${dlib_LIBS})
TARGET_LINK_LIBRARIES(findTemplate2D ${dlib_LIBS} ${OpenCV_LIBS})
