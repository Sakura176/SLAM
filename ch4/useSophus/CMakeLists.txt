cmake_minimum_required(VERSION 3.16)
find_package( Sophus REQUIRED) 
set(CMAKE_CXX_FLAGS "-std=c++11")
include_directories( ${Sophus_INCLUDE_DIRS})
include_directories( "/usr/include/eigen3")

add_executable( useSophus useSophus.cpp )
target_link_libraries(useSophus fmt)