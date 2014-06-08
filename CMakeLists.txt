cmake_minimum_required(VERSION 2.8)

project(AudioTK)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

enable_testing()

option(ENABLE_PROFILING "Enable the internal perf counter" OFF)
option(ENABLE_PYTHON "Enable the Python wrappers" OFF)

if(ENABLE_PROFILING)
  set(ENABLE_INTERNAL_PROFILING 1)
else(ENABLE_PROFILING)
  set(ENABLE_INTERNAL_PROFILING 0)
endif(ENABLE_PROFILING)

find_package(Git REQUIRED)
find_package(Boost REQUIRED unit_test_framework timer system)

find_package(libsndfile)
if(LIBSNDFILE_FOUND)
  set(USE_LIBSNDFILE 1)
else(LIBSNDFILE_FOUND)
  set(USE_LIBSNDFILE 0)
endif(LIBSNDFILE_FOUND)

if(ATK_BUILD_PYTHON)
  find_package(swig REQUIRED)
  find_package(Numpy REQUIRED)
endif(ATK_BUILD_PYTHON)

GIT_WC_INFO(${PROJECT_SOURCE_DIR} ATK)

find_package(FFTW)

SET(USE_FFTW 0)
SET(USE_ACCELERATE 0)

if(FFTW_FOUND)
  SET(USE_FFTW 1)
  include_directories(${FFTW_INCLUDES})
  SET(FFTLIBRARIES ${FFTW_LIBRARIES})
else(FFTW_FOUND)
  if(APPLE)
    if(ACCELERATE_FRAMEWORK_FOUND)
      FIND_PACKAGE(Accelerate REQUIRED)
      SET(FFTLIBRARIES ${ACCELERATE_FRAMEWORK_LINK_FLAGS})
      SET(USE_ACCELERATE 1)
    endif(ACCELERATE_FRAMEWORK_FOUND)
  endif(APPLE)
endif(FFTW_FOUND)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "ATK/config.h.in"
  "ATK/config.h"
  )

INSTALL(FILES ${PROJECT_BINARY_DIR}/ATK/config.h
   DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ATK
    )

include_directories(${PROJECT_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(ATK)
add_subdirectory(tests)

if(ENABLE_PYTHON)
  add_subdirectory(Python)
endif(ENABLE_PYTHON)

