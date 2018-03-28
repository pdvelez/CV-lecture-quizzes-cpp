cmake_minimum_required(VERSION 3.7)
project(2A-L6)

#find_package( dlib REQUIRED )
find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 11)

set(forYourEyesOnly_src src/forYourEyesOnly.cpp)

add_executable(forYourEyesOnly ${forYourEyesOnly_src})

TARGET_LINK_LIBRARIES(forYourEyesOnly ${OpenCV_LIBS})
