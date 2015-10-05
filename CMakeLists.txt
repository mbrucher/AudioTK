cmake_minimum_required(VERSION 2.8)

project(AudioTK)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_TESTS "Enable tests generation" ON)
option(ENABLE_SHARED_LIBRARIES "Enable shared libraries generation" ON)
option(ENABLE_STATIC_LIBRARIES "Enable static libraries generation" OFF)
option(ENABLE_THREADS "Enable thread pool support" ON)

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
  find_package(Boost REQUIRED timer)
else(ENABLE_PROFILING)
  set(ENABLE_INTERNAL_PROFILING 0)
endif(ENABLE_PROFILING)

if(ENABLE_THREADS)
  find_package(TBB REQUIRED)
  set(USE_THREADPOOL 1)
  if(ENABLE_THREADS)
    include_directories(${TBB_INCLUDE_DIR})
  endif(ENABLE_THREADS)
else(ENABLE_THREADS)
  set(USE_THREADPOOL 0)
endif(ENABLE_THREADS)

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

if(ENABLE_TESTS)
  find_package(Boost REQUIRED unit_test_framework system)
endif(ENABLE_TESTS)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "ATK/config.h.in"
  "ATK/config.h"
  )

include_directories(${PROJECT_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIR})

macro(stagedebug target)
  if(APPLE)
    add_custom_command(TARGET ${target}
      POST_BUILD
      COMMAND dsymutil $<TARGET_FILE_NAME:${target}>
      MAIN_DEPENDENCY ${target}
      COMMENT "Staging dSYM for ${target}"
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
      VERBATIM)
  endif()
endmacro()

MACRO(SOURCE_GROUP_BY_FOLDER target)
  SET(SOURCE_GROUP_DELIMITER "/")

  SET(last_dir "")
  SET(files "")
  FOREACH(file ${${target}_SRC} ${${target}_HEADERS})
    file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}/ATK" ${file})
    GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
    IF (NOT "${dir}" STREQUAL "${last_dir}")
      IF (files)
        SOURCE_GROUP("${last_dir}" FILES ${files})
      ENDIF (files)
      SET(files "")
    ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
    SET(files ${files} ${file})
    SET(last_dir "${dir}")
  ENDFOREACH(file)
  IF (files)
    SOURCE_GROUP("${last_dir}" FILES ${files})
  ENDIF (files)
ENDMACRO(SOURCE_GROUP_BY_FOLDER)

add_subdirectory(ATK)
if(ENABLE_TESTS)
  add_subdirectory(tests)
endif(ENABLE_TESTS)

if(ENABLE_PYTHON)
  add_subdirectory(Python)
endif(ENABLE_PYTHON)
