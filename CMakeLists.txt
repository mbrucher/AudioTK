cmake_minimum_required(VERSION 3.5)

project(AudioTK)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ATK_VERSION 3.2.0)
set(ATK_CURRENTLY_BUILDING ON)

option(ENABLE_TESTS "Enable tests generation" ON)
option(ENABLE_PROFILE_INFO "Enable profile info" OFF)
option(ENABLE_PROFILING "Enable the internal time counter" OFF)
option(ENABLE_SHARED_LIBRARIES "Enable shared libraries generation" ON)
option(ENABLE_STATIC_LIBRARIES "Enable static libraries generation" OFF)
option(ENABLE_PYTHON "Enable Python support" ON)
option(ENABLE_THREADS "Enable thread pool support" OFF)
option(ENABLE_SIMD "Enable SIMD support" OFF)
option(ENABLE_GPL "Enable GPL library support like FFTW and LIBSNDFILE" OFF)
option(ENABLE_CODECOVERAGE "Generate code coverage data" OFF)
option(ENABLE_ADDRESS_SANITIZER "Activate address sanitizer support" OFF)
option(BUILD_DOC "Build Doxygen documentation" OFF)
option(DISABLE_EIGEN_WARNINGS "Removes lots of Eigen warnings" OFF)
option(DISABLE_PYTHON_TESTS "Don't test Python modules" OFF) #Use this for CI

message(STATUS " Build SIMD: ${ENABLE_SIMD}")
message(STATUS " Build shared libraries: ${ENABLE_SHARED_LIBRARIES}")
message(STATUS " Build static libraries: ${ENABLE_STATIC_LIBRARIES}")
message(STATUS " Build tests: ${ENABLE_TESTS}")

enable_testing()

if(ENABLE_PYTHON)
  add_subdirectory(${CMAKE_SOURCE_DIR}/3rdParty/pybind11)

  LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdParty/pybind11/tools)
  FIND_PACKAGE(PythonLibsNew REQUIRED)
endif(ENABLE_PYTHON)

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/3rdParty/eigen)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/3rdParty/gsl/include)

if(ENABLE_SIMD)
  SET(USE_SIMD 0)
else(ENABLE_SIMD)
  SET(USE_SIMD 0)
endif(ENABLE_SIMD)

if(ENABLE_TESTS)
 if(NOT ENABLE_SHARED_LIBRARIES)
  message (ERROR " Tests depend on shared libraries to run")
 endif(NOT ENABLE_SHARED_LIBRARIES)
endif(ENABLE_TESTS)

if(ENABLE_PYTHON)
 if(NOT ENABLE_SHARED_LIBRARIES)
  message (ERROR " Python support depends on shared libraries to run")
 endif(NOT ENABLE_SHARED_LIBRARIES)
endif(ENABLE_PYTHON)

if(ENABLE_CODECOVERAGE)
  SET(CMAKE_BUILD_TYPE "Coverage" CACHE STRING "" FORCE)
  include(CodeCoverage)
  setup_target_for_coverage(codecoverage "make test" coverage)
  SET(ENABLE_INSTANTIATION 0)
else(ENABLE_CODECOVERAGE)
  SET(ENABLE_INSTANTIATION 1)
endif(ENABLE_CODECOVERAGE)

IF(NOT DEFINED PYTHON_INSTALL_FOLDER)
  set(PYTHON_INSTALL_FOLDER "${CMAKE_INSTALL_PREFIX}/lib/")
ENDIF(NOT DEFINED PYTHON_INSTALL_FOLDER)

if(ENABLE_PROFILING)
  set(ENABLE_INTERNAL_PROFILING 1)
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

if(ENABLE_GPL)
  find_package(libsndfile)

  if(LIBSNDFILE_FOUND)
    set(USE_LIBSNDFILE 1)
  else(LIBSNDFILE_FOUND)
    set(USE_LIBSNDFILE 0)
  endif(LIBSNDFILE_FOUND)
endif(ENABLE_GPL)

find_package(IPP)
find_package(Boost REQUIRED)

SET(USE_FFTW 0)
SET(USE_IPP 0)

if(HAVE_IPP)
  include_directories(${IPP_INCLUDE_DIRS})
  SET(FFT_INCLUDES ${IPP_INCLUDE_DIRS})
  SET(FFT_LIBRARIES ${IPP_LIBRARIES})
  SET(FFTLIBRARIES ${IPP_LIBRARIES})
  SET(USE_IPP 1)
else(HAVE_IPP)
  if(ENABLE_GPL)
    FIND_PACKAGE(FFTW REQUIRED)
    SET(USE_FFTW 1)
    include_directories(${FFTW_INCLUDES})
    SET(FFT_INCLUDES ${FFTW_INCLUDES})
    SET(FFT_LIBRARIES ${FFTW_LIBRARIES})
    SET(FFTLIBRARIES ${FFTW_LIBRARIES})
  else(ENABLE_GPL)
    MESSAGE(FATAL_ERROR "No FFT support")
  endif(ENABLE_GPL)
endif(HAVE_IPP)

if(ENABLE_TESTS)
  find_package(Boost REQUIRED unit_test_framework system)
endif(ENABLE_TESTS)

include(Utilities)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "ATK/config.h.in"
  "ATK/config.h" @ONLY
  )
configure_file (
  "atk-config.cmake.in"
  "atk-config.cmake" @ONLY
  )

INSTALL(FILES ${PROJECT_BINARY_DIR}/atk-config.cmake
 DESTINATION ${CMAKE_INSTALL_PREFIX}
 )

include_directories(${CMAKE_BINARY_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

add_subdirectory(ATK)
if(ENABLE_TESTS)
  find_package(Boost REQUIRED unit_test_framework system)
  ADD_DEFINITIONS("-DBOOST_ALL_NO_LIB")
  add_subdirectory(tests)
  add_subdirectory(profiling)
endif(ENABLE_TESTS)

if(ENABLE_PYTHON)
  add_subdirectory(Python/ATK)
endif(ENABLE_PYTHON)

add_subdirectory(modules)

FILE(GLOB CMAKE_OTHER_SRC CMake/*.cmake *.in ATK/*.in *.yml *.md *.properties *.py scripts/*.sh)
SOURCE_GROUP_BY_FOLDER(CMAKE_OTHER)
add_custom_target(CMake SOURCES ${CMAKE_OTHER_SRC})

IF (BUILD_DOC)
  FIND_PACKAGE(Doxygen REQUIRED)

  SET(DOXYGEN_INPUT Doxyfile)
  SET(DOXYGEN_OUTPUT Doxygen)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${DOXYGEN_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
    COMMAND ${CMAKE_COMMAND} -E echo "Done."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${DOXYGEN_INPUT}
    )

  ADD_CUSTOM_TARGET(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

  ADD_CUSTOM_TARGET(apidoc_forced
    COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
    COMMAND ${CMAKE_COMMAND} -E echo "Done."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
ENDIF (BUILD_DOC)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
ENDIF()
