cmake_minimum_required(VERSION 3.7)
project(2A-L5)

find_package( dlib REQUIRED )
find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 11)

set(gradientQuiz_src src/gradientQuiz.cpp)

add_executable(gradientQuiz ${gradientQuiz_src})

TARGET_LINK_LIBRARIES(gradientQuiz ${OpenCV_LIBS})
