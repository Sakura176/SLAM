# SLAM学习
记录学习SLAM十四讲的过程，以高翔老师的[视觉SLAM十四讲](https://github.com/gaoxiang12/slambook)为教程


# 错误记录

### 错误描述1
```
CMake Error at CMakeLists.txt:20 (find_package):
  By not providing "FindG2O.cmake" in CMAKE_MODULE_PATH this project has
  asked CMake to find a package configuration file provided by "G2O", but
  CMake did not find one.

  Could not find a package configuration file provided by "G2O" with any of
  the following names:

    G2OConfig.cmake
    g2o-config.cmake

  Add the installation prefix of "G2O" to CMAKE_PREFIX_PATH or set "G2O_DIR"
  to a directory containing one of the above files.  If "G2O" provides a
  separate development package or SDK, be sure it has been installed.
  ```
  ### 解决方案
  ```bash
  cd g2o/cmake_modules
  sudo cp FindG2O.cmake /usr/share/cmake-3.16/Modules
  ```