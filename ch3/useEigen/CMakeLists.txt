# 声明要求的cmake最低版本
cmake_minimum_required( VERSION 2.8)

# 声明一个cmake工程
project( EigenMatrix )

add_executable( EigenMatrix EigenMatrix.cpp)

include_directories("/usr/include/eigen3")