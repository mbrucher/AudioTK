cmake_minimum_required(VERSION 2.8)

project(AudioTK)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_TESTS "Enable tests generation" ON)
option(ENABLE_PROFILE_INFO "Enable profile info" OFF)
option(ENABLE_SHARED_LIBRARIES "Enable shared libraries generation" ON)
option(ENABLE_STATIC_LIBRARIES "Enable static libraries generation" OFF)
option(ENABLE_THREADS "Enable thread pool support" OFF)

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

include(CheckCXXCompilerFlag)
include(CMakePushCheckState)
include(CheckCXXSourceRuns)

if(WIN32)
  SET(NATVIS_FILE ${PROJECT_SOURCE_DIR}/atk.natvis)
  SET_SOURCE_FILES_PROPERTIES(${NATVIS_FILE} LANGUAGE natvis)

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
  endif("${MSVC_RUNTIME}" STREQUAL "Static")

  CHECK_CXX_COMPILER_FLAG("/Qstd=c++11" COMPILER_SUPPORTS_CXX11)
   if(COMPILER_SUPPORTS_CXX11)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qstd=c++11")
   else(COMPILER_SUPPORTS_CXX11)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /QC++11.")
   endif(COMPILER_SUPPORTS_CXX11)

  CHECK_CXX_COMPILER_FLAG("/fp:fast" COMPILER_SUPPORTS_fastmath)
  if(COMPILER_SUPPORTS_fastmath)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
  else(COMPILER_SUPPORTS_fastmath)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /fp:fast.")
  endif(COMPILER_SUPPORTS_fastmath)

  if(ENABLE_PROFILE_INFO)
    CHECK_CXX_COMPILER_FLAG("/Qvec-report:2" COMPILER_SUPPORTS_vectorreport)
    if(COMPILER_SUPPORTS_vectorreport)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qvec-report:2")
    else(COMPILER_SUPPORTS_vectorreport)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qvec-report:2.")
    endif(COMPILER_SUPPORTS_vectorreport)

    CHECK_CXX_COMPILER_FLAG("/Qopt-report:2 /Qopt-report-phase=vec" COMPILER_SUPPORTS_vectorreport1)
    if(COMPILER_SUPPORTS_vectorreport1)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qopt-report:2 /Qopt-report-phase=vec")
    else(COMPILER_SUPPORTS_vectorreport1)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qopt-report:2 /Qopt-report-phase=vec.")
    endif(COMPILER_SUPPORTS_vectorreport1)
  endif(ENABLE_PROFILE_INFO)

  CHECK_CXX_COMPILER_FLAG("/Qrestrict" COMPILER_SUPPORTS_restrict)
  if(COMPILER_SUPPORTS_restrict)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qrestrict")
  else(COMPILER_SUPPORTS_restrict)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qrestrict.")
  endif(COMPILER_SUPPORTS_restrict)

  CHECK_CXX_COMPILER_FLAG("/Qftz" COMPILER_SUPPORTS_ftz)
  if(COMPILER_SUPPORTS_ftz)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qftz")
  else(COMPILER_SUPPORTS_ftz)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qftz.")
  endif(COMPILER_SUPPORTS_ftz)

  CHECK_CXX_COMPILER_FLAG("/QxAVX /QaxCORE-AVX2" COMPILER_SUPPORTS_AVX)
  if(COMPILER_SUPPORTS_AVX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /QxAVX /QaxCORE-AVX2")
  else(COMPILER_SUPPORTS_AVX)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /QxAVX /QaxCORE-AVX2.")
  endif(COMPILER_SUPPORTS_AVX)

  add_definitions(-DHAS_STD_ALIGN)
else(WIN32)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
   if(COMPILER_SUPPORTS_CXX11)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   else(COMPILER_SUPPORTS_CXX11)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support C++11.")
   endif(COMPILER_SUPPORTS_CXX11)

   CHECK_CXX_COMPILER_FLAG("-pthread" COMPILER_SUPPORTS_PTHREAD)
   if(COMPILER_SUPPORTS_PTHREAD)
     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
     set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pthread")
   else(COMPILER_SUPPORTS_PTHREAD)
      message(STATUS "The linker ${CMAKE_CXX_COMPILER} doesn't support -pthread.")
   endif(COMPILER_SUPPORTS_PTHREAD)

  if(ENABLE_PROFILE_INFO)
    CHECK_CXX_COMPILER_FLAG("-qopt-report:2 -qopt-report-phase=vec" COMPILER_SUPPORTS_vectorreport)
    if(COMPILER_SUPPORTS_vectorreport)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -qopt-report:2 -opt-report-phase=vec")
    else(COMPILER_SUPPORTS_vectorreport)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -qopt-report:2 -qopt-report-phase=vec.")
    endif(COMPILER_SUPPORTS_vectorreport)

    CHECK_CXX_COMPILER_FLAG("-fopt-info" COMPILER_SUPPORTS_fopt_info)
    if(COMPILER_SUPPORTS_fopt_info)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopt-info")
    else(COMPILER_SUPPORTS_fopt_info)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -fopt-info.")
    endif(COMPILER_SUPPORTS_fopt_info)
  endif(ENABLE_PROFILE_INFO)

  CHECK_CXX_COMPILER_FLAG("-restrict" COMPILER_SUPPORTS_restrict)
  if(COMPILER_SUPPORTS_restrict)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -restrict")
  else(COMPILER_SUPPORTS_restrict)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -restrict.")
  endif(COMPILER_SUPPORTS_restrict)

  CHECK_CXX_COMPILER_FLAG("-ftz" COMPILER_SUPPORTS_ftz)
  if(COMPILER_SUPPORTS_ftz)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftz")
  else(COMPILER_SUPPORTS_ftz)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -ftz.")
  endif(COMPILER_SUPPORTS_ftz)

  CHECK_CXX_COMPILER_FLAG("-fdenormal-fp-math=positive-zero" COMPILER_SUPPORTS_ftpz)
  if(COMPILER_SUPPORTS_ftpz)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdenormal-fp-math=positive-zero")
  else(COMPILER_SUPPORTS_ftpz)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -fdenormal-fp-math=positive-zero.")
  endif(COMPILER_SUPPORTS_ftpz)
  
  CHECK_CXX_COMPILER_FLAG("-ftree-vectorize -ftree-vectorizer-verbose=2" COMPILER_SUPPORTS_ftree_vectorize)
  if(COMPILER_SUPPORTS_ftree_vectorize)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftree-vectorize -ftree-vectorizer-verbose=2")
  else(COMPILER_SUPPORTS_ftree_vectorize)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -ftree-vectorize  -ftree-vectorizer-verbose.")
  endif(COMPILER_SUPPORTS_ftree_vectorize)

#  CHECK_CXX_COMPILER_FLAG("-ffast-math" COMPILER_SUPPORTS_fast_math)
#  if(COMPILER_SUPPORTS_fast_math)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
#  else(COMPILER_SUPPORTS_fast_math)
#     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -ffast-math.")
#  endif(COMPILER_SUPPORTS_fast_math)

  CHECK_CXX_COMPILER_FLAG("-xAVX -axCORE-AVX2" COMPILER_SUPPORTS_AVX)
  if(COMPILER_SUPPORTS_AVX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -xAVX -axCORE-AVX2")
  else(COMPILER_SUPPORTS_AVX)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -xAVX -axCORE-AVX2.")
  endif(COMPILER_SUPPORTS_AVX)

  cmake_push_check_state()
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -std=c++11")
  check_cxx_source_runs("
  #include <memory>

  int main()
  {
    std::size_t alignment = 32;
    std::size_t size = 32;
    std::size_t space = 32;
    void* p = nullptr;

    std::align(alignment, size, p, space);

    return 0;
  }
" HAS_STD_ALIGN)
  cmake_pop_check_state()

  if(HAS_STD_ALIGN)
    add_definitions(-DHAS_STD_ALIGN)
  endif(HAS_STD_ALIGN)

endif(WIN32)

enable_testing()

option(ENABLE_PROFILING "Enable the internal perf counter" OFF)
option(ENABLE_PYTHON "Enable the Python wrappers" OFF)

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

find_package(libsndfile)

if(LIBSNDFILE_FOUND)
  set(USE_LIBSNDFILE 1)
else(LIBSNDFILE_FOUND)
  set(USE_LIBSNDFILE 0)
endif(LIBSNDFILE_FOUND)

if(ATK_BUILD_PYTHON)
  find_package(swig REQUIRED)
  find_package(NumPy REQUIRED)
endif(ATK_BUILD_PYTHON)

find_package(FFTW)
find_package(Boost REQUIRED)
find_package(Eigen)

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
  find_package(Boost REQUIRED unit_test_framework system)
  add_subdirectory(tests)
  add_subdirectory(profiling)
endif(ENABLE_TESTS)

if(ENABLE_PYTHON)
  add_subdirectory(Python)
endif(ENABLE_PYTHON)

FIND_PACKAGE(Doxygen)

IF (DOXYGEN_FOUND)

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

ENDIF (DOXYGEN_FOUND)
