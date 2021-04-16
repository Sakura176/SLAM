cmake_minimum_required( VERSION 3.0 )

# 添加C++11标准
set(CMAKE_CXX_FLAGS "-std=c++11")

project(question)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( question_1 question_1.cpp)
target_link_libraries(question_1 ${OpenCV_LIBS})

add_executable( question_2 question_2.cpp)
target_link_libraries(question_2 ${OpenCV_LIBS})
include_directories("/usr/include/eigen3")

add_executable( question_3 question_3.cpp)
target_link_libraries(question_3 ${OpenCV_LIBS})