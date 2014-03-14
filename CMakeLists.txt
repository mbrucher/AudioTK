cmake_minimum_required(VERSION 2.8)

project(AudioTK)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

enable_testing()

find_package(Git REQUIRED)
find_package(Boost REQUIRED unit_test_framework)

find_package(libsndfile)
if(LIBSNDFILE_FOUND)
  set(USE_LIBSNDFILE 1)
else(LIBSNDFILE_FOUND)
  set(USE_LIBSNDFILE 0)
endif(LIBSNDFILE_FOUND)

if(ATK_BUILD_PYTHON)
  find_package(swig REQUIRED)
endif(ATK_BUILD_PYTHON)

GIT_WC_INFO(${PROJECT_SOURCE_DIR} ATK)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "ATK/config.h.in"
  "ATK/config.h"
  )

include_directories(${Boost_INCLUDE_DIR})

if(APPLE)
  FIND_PACKAGE(Accelerate REQUIRED)
  SET(FFTLIBRARIES ${ACCELERATE_FRAMEWORK_LINK_FLAGS})
endif(APPLE)

add_subdirectory(ATK)
add_subdirectory(tests)

if(ATK_BUILD_PYTHON)
  add_subdirectory(Python)
endif(ATK_BUILD_PYTHON)

