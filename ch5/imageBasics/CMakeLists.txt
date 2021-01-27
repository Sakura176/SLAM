cmake_minimum_required(VERSION 3.0)
# 添加C++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )

project(imageBasics)

# 寻找OpenCV库
find_package( OpenCV REQUIRED )

# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( imageBasics imageBasics.cpp )

# 链接OpenCV库
target_link_libraries( imageBasics ${OpenCV_LIBS} )

add_executable( undistort undistortImage.cpp)

target_link_libraries( undistort ${OpenCV_LIBS} )