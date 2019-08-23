#File copied from Yue Kang's and Christian Berger's
 
cmake_minimum_required(VERSION 3.2)
project(main)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OPENDLV_MESSAGE_SET messages.odvd)
set(CLUON_COMPLETE cluon-complete.hpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(LIBRARIES Threads::Threads)


################################################################################
# Extract cluon-msc from cluon-complete.hpp
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/cluon-msc
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/src/control/${CLUON_COMPLETE} ${CMAKE_BINARY_DIR}/cluon-complete.hpp
    COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/src/control/${CLUON_COMPLETE} ${CMAKE_BINARY_DIR}/cluon-complete.cpp
    COMMAND ${CMAKE_CXX_COMPILER} -o ${CMAKE_BINARY_DIR}/cluon-msc ${CMAKE_BINARY_DIR}/cluon-complete.cpp -std=c++14 -pthread -DHAVE_CLUON_MSC
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/control/${CLUON_COMPLETE})

################################################################################
# Generate message.hpp using cluon-msc
add_custom_target(messages.hpp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_BINARY_DIR}/cluon-msc --cpp --out=${CMAKE_BINARY_DIR}/messages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/control/${OPENDLV_MESSAGE_SET}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/control/${OPENDLV_MESSAGE_SET} ${CMAKE_BINARY_DIR}/cluon-msc)


file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/cv/*.h
    ${PROJECT_SOURCE_DIR}/src/cv/*.cpp
    ${PROJECT_SOURCE_DIR}/src/control/*.h
    ${PROJECT_SOURCE_DIR}/src/control/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

include_directories(SYSTEM ${CMAKE_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_dependencies(${PROJECT_NAME} messages.hpp)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

################################################################################
# OpenCV 
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


target_link_libraries(main ${OpenCV_LIBS})