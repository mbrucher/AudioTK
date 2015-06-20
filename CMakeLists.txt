cmake_minimum_required(VERSION 2.8)

project(AudioTK)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

option(ENABLE_TESTS "Enable tests generation" ON)
option(ENABLE_SHARED_LIBRARIES "Enable shared libraries generation" ON)
option(ENABLE_STATIC_LIBRARIES "Enable static libraries generation" OFF)

message(INFO " Build shared libraries: ${ENABLE_SHARED_LIBRARIES}")
message(INFO " Build static libraries: ${ENABLE_STATIC_LIBRARIES}")
message(INFO " Build tests: ${ENABLE_TESTS}")

if(${ENABLE_TESTS} STREQUAL "ON")
 if(${ENABLE_SHARED_LIBRARIES} STREQUAL "OFF")
  message (ERROR " Tests depend on shared libraries to run")
 endif(${ENABLE_SHARED_LIBRARIES} STREQUAL "OFF")
endif(${ENABLE_TESTS} STREQUAL "ON")

IF(NOT DEFINED PYTHON_INSTALL_FOLDER)
  set(PYTHON_INSTALL_FOLDER "${CMAKE_INSTALL_PREFIX}/lib/")
ENDIF(NOT DEFINED PYTHON_INSTALL_FOLDER)

if(WIN32)
set(MSVC_RUNTIME "Dynamic" CACHE STRING "Set up MSVC Runtime (Dynamic/Static)")

if("${MSVC_RUNTIME}" STREQUAL "Static")
  set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
endif()
endif(WIN32)

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

GIT_WC_INFO(${PROJECT_SOURCE_DIR} ATK)
configure_file (
  "ATK/git.h.in"
  "ATK/git.h"
  )

include_directories(${PROJECT_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIR})

macro(stagedebug target)
  if(APPLE)
    add_custom_command(TARGET ${target}
      POST_BUILD
      COMMAND dsymutil $<TARGET_FILE_NAME:${target}> -o ${CMAKE_INSTALL_PREFIX}/lib/$<TARGET_FILE_NAME:${target}>.dSYM
      MAIN_DEPENDENCY ${target}
      COMMENT "Staging dSYM for ${target}"
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
      VERBATIM)
  endif()
endmacro()

add_subdirectory(ATK)
if(ENABLE_TESTS)
  add_subdirectory(tests)
endif(ENABLE_TESTS)

if(ENABLE_PYTHON)
  add_subdirectory(Python)
endif(ENABLE_PYTHON)
