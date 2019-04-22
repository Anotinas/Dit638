cmake_minimum_required(VERSION 3.1)
PROJECT (cv)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)
SET(OpenCV_INCLUDE_DIRS /usr/local/Cellar/opencv/4.1.0_1/include)
SET(OpenCV_LIBS /usr/local/Cellar/opencv/4.1.0_1/lib)
SET(OpenCV_DIR /usr/local/Cellar/opencv/4.1.0_1/lib/cmake/opencv4/)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})
target_link_libraries(main ${OpenCV_LIBS})