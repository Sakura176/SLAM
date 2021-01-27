# 声明要求的cmake最低版本
cmake_minimum_required( VERSION 2.8)

# 声明一个cmake工程
project( UseGeometry )

add_executable( UseGeometry useGeometry.cpp)

include_directories("/usr/include/eigen3")