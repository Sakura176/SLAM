# 寻找OpenCV库
find_package( OpenCV REQUIRED )
find_package(Pangolin REQUIRED)


add_executable(stereoVision stereoVision.cpp)
target_link_libraries(stereoVision ${OpenCV_LIBS} ${Pangolin_LIBRARIES})