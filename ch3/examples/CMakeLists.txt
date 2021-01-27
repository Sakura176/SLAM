cmake_minimum_required( VERSION 3.0 )

project(CoorTran)

add_executable(CoorTran coordinateTransform.cpp)

include_directories("/usr/include/eigen3")