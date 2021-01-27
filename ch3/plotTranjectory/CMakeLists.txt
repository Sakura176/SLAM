cmake_minimum_required( VERSION 3.0)

project(PlotTra)

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")

add_executable(PlotTra plotTrajectory.cpp)

# 链接库文件时必须加上可执行文件名
target_link_libraries(PlotTra ${Pangolin_LIBRARIES})