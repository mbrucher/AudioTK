cmake_minimum_required(VERSION 2.8)

project(AudioTK)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

find_package(Git REQUIRED)
find_package(Boost REQUIRED unit_test_framework)

GIT_WC_INFO(${PROJECT_SOURCE_DIR} ATK)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "ATK/config.h.in"
  "ATK/config.h"
  )

add_subdirectory(ATK)
add_subdirectory(tests)

