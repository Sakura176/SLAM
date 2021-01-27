cmake_minimum_required( VERSION 3.0 )

project( sift_cv )

# opencv
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(sift_cv sift_cv.cpp)
target_link_libraries(sift_cv ${OpenCV_LIBS})